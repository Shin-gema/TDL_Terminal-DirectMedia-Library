
#include "tdl/Matrix/PixelMatrix.hpp"
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>
#include <map>
#include <unordered_map>

namespace tdl {

    std::map<std::vector<std::pair<int, int>>, const char *> PixelCharMap = {
            {{{0,0}},  "🬀"},
            {{{0,1}}, "🬁"},
            {{{0,0},{0,1}}, "🬂"},
            {{{1,0}}, "🬃"},
            {{{0,0},{1,0}}, "🬄"},
            {{{0,1},{1,0}}, "🬅"},
            {{{0,0},{0,1},{1,0}}, "🬆"},
            {{{1,1}}, "🬇"},
            {{{0,0},{1,1}}, "🬈"},
            {{{0,1},{1,1}}, "🬉"},
            {{{0,0},{0,1},{1,1}}, "🬊"},
            {{{1,0},{1,1}}, "🬋"},
            {{{0,0},{1,0},{1,1}}, "🬌"},
            {{{0,1},{1,0},{1,1}}, "🬍"},
            {{{0,0},{0,1},{1,0},{1,1}}, "🬎"},
            {{{2,0}}, "🬏"},
            {{{0,0},{2,0}}, "🬐"},
            {{{0,1},{2,0}}, "🬑"},
            {{{0,0},{0,1},{2,0}}, "🬒"},
            {{{1,0},{2,0}}, "🬓"},
            {{{0,0},{1,0},{2,0}}, "▌"},
            {{{0,1},{1,0},{2,0}}, "🬔"},
            {{{0,0},{0,1},{1,0},{2,0}}, "🬕"},
            {{{1,1},{2,0}}, "🬖"},
            {{{0,0},{1,1},{2,0}}, "🬗"},
            {{{0,1},{1,1},{2,0}}, "🬘"},
            {{{0,0},{0,1},{1,1},{2,0}}, "🬙"},
            {{{1,0},{1,1},{2,0}}, "🬚"},
            {{{0,0},{1,0},{1,1},{2,0}}, "🬛"},
            {{{0,1},{1,0},{1,1},{2,0}}, "🬜"},
            {{{0,0},{0,1},{1,0},{1,1},{2,0}}, "🬝"},
            {{{2,1}}, "🬞"},
            {{{0,0},{2,1}}, "🬟"},
            {{{0,1},{2,1}}, "🬠"},
            {{{0,0},{0,1},{2,1}}, "🬡"},
            {{{1,0},{2,1}}, "🬢"},
            {{{0,0},{1,0},{2,1}}, "🬣"},
            {{{0,1},{1,0},{2,1}}, "🬤"},
            {{{0,0},{0,1},{1,0},{2,1}}, "🬥"},
            {{{1,1},{2,1}}, "🬦"},
            {{{0,0},{1,1},{2,1}}, "🬧"},
            {{{0,1},{1,1},{2,1}}, "🮈"},
            {{{0,0},{0,1},{1,1},{2,1}}, "🬨"},
            {{{1,0},{1,1},{2,1}}, "🬩"},
            {{{0,0},{1,0},{1,1},{2,1}}, "🬪"},
            {{{0,1},{1,0},{1,1},{2,1}}, "🬫"},
            {{{0,0},{0,1},{1,0},{1,1},{2,1}}, "🬬"},
            {{{2,0},{2,1}}, "🬭"},
            {{{0,0},{2,0},{2,1}}, "🬮"},
            {{{0,1},{2,0},{2,1}}, "🬯"},
            {{{0,0},{0,1},{2,0},{2,1}}, "🬰"},
            {{{1,0},{2,0},{2,1}}, "🬱"},
            {{{0,0},{1,0},{2,0},{2,1}}, "🬲"},
            {{{0,1},{1,0},{2,0},{2,1}}, "🬳"},
            {{{0,0},{0,1},{1,0},{2,0},{2,1}}, "🬴"},
            {{{1,1},{2,0},{2,1}}, "🬵"},
            {{{0,0},{1,1},{2,0},{2,1}}, "🬶"},
            {{{0,1},{1,1},{2,0},{2,1}}, "🬷"},
            {{{0,0},{0,1},{1,1},{2,0},{2,1}}, "🬸"},
            {{{1,0},{1,1},{2,0},{2,1}}, "🬹"},
            {{{0,0},{1,0},{1,1},{2,0},{2,1}}, "🬺"},
            {{{0,1},{1,0},{1,1},{2,0},{2,1}}, "🬻"},
            {{{0,0},{0,1},{1,0},{1,1},{2,0},{2,1}}, "█"}
    };


    PixelMatrix::PixelMatrix() : _size(Vector2u(0, 0)) {
    }

    PixelMatrix::PixelMatrix(Vector2u size) : _size(std::move(size)) {
        _pixelsTab = std::vector<Pixel>(_size.x() * _size.y(), Pixel(0, 0, 0, 255));
    }


    PixelMatrix::~PixelMatrix() {}

    void PixelMatrix::setPixel(const Vector2u &pos, Pixel &color) {
        if (pos.x() < _size.x() && pos.y() < _size.y()) {
            _pixelsTab[pos.y() * _size.x() + pos.x()] = color;
        }
    }

    void PixelMatrix::getPixelChar(Vector2u pos, Pixel* pixels) {

        if (pos.x() + 2 < _size.x() && pos.y() + 3 < _size.y()) {
            pixels[0] = _pixelsTab[pos.y() * _size.x() + pos.x()];
            pixels[1] = _pixelsTab[pos.y() * _size.x() + pos.x() + 1];
            pixels[2] = _pixelsTab[(pos.y() + 1) * _size.x() + pos.x()];
            pixels[3] = _pixelsTab[(pos.y() + 1) * _size.x() + pos.x() + 1];
            pixels[4] = _pixelsTab[(pos.y() + 2) * _size.x() + pos.x()];
            pixels[5] = _pixelsTab[(pos.y() + 2) * _size.x() + pos.x() + 1];
        } else {
            throw std::out_of_range("The position is out of range");
        }
    }

    void PixelMatrix::setPixelChar(tdl::Vector2u pos, Pixel* pixels)
    {
        if (pos.x() + 2 < _size.x() && pos.y() + 3 < _size.y()) {
            _pixelsTab[pos.y() * _size.x() + pos.x()] = pixels[0];
            _pixelsTab[pos.y() * _size.x() + pos.x() + 1] = pixels[1];
            _pixelsTab[(pos.y() + 1) * _size.x() + pos.x()] = pixels[2];
            _pixelsTab[(pos.y() + 1) * _size.x() + pos.x() + 1] = pixels[3];
            _pixelsTab[(pos.y() + 2) * _size.x() + pos.x()] = pixels[4];
            _pixelsTab[(pos.y() + 2) * _size.x() + pos.x() + 1] = pixels[5];
        } 
    }

    /**
 * @brief compute the color of the char at the position pos
 *
 * @param pos the position of the char
 * @return CharColor the color of the char
 */
    tdl::CharColor tdl::PixelMatrix::computeCharColor(Vector2u pos, Pixel* pixels)
    {
        CharColor charColor;
        std::map<Pixel, std::vector<std::pair<int, int>>> pixelGroups;

        for (int y = 0; y < 3; ++y) {
            for (int x = 0; x < 2; ++x) {
                Pixel pixel = pixels[y * 2 + x];
                pixelGroups[pixel].push_back({y, x});
            }
        }

        size_t maxCount1 = 0, maxCount2 = 0;
        for (const auto& pair : pixelGroups) {
            if (pair.second.size() > maxCount1) {
                charColor.BackGround = charColor.ForeGround;
                maxCount2 = maxCount1;
                charColor.ForeGround = pair.first;
                maxCount1 = pair.second.size();
            } else if (pair.second.size() > maxCount2) {
                charColor.BackGround = pair.first;
                maxCount2 = pair.second.size();
            }
        }
        charColor.shape = PixelCharMap[pixelGroups[charColor.ForeGround]];
        return charColor;
    }

    void PixelMatrix::append(std::vector<Pixel> &pixels) {
        _pixelsTab.insert(_pixelsTab.end(), pixels.begin(), pixels.end());
        _size = Vector2u(pixels.size() > _size.x() ? pixels.size() : _size.x(), _size.y() + 1);}

    void PixelMatrix::resize(Vector2u &size) {
        _size = size;
        _pixelsTab.resize(_size.x() * _size.y(), Pixel(0, 0, 0, 255));
    }

    void PixelMatrix::clear() {
        std::fill(_pixelsTab.begin(), _pixelsTab.end(), Pixel(0, 0, 0, 255));
    }

}
