
#include "tdl/Matrix/PixelMatrix.hpp"
#include <algorithm>
#include <iterator>
#include <vector>


namespace tdl {


    PixelMatrix::PixelMatrix() : _size(Vector2u(0, 0)) {
    }

    PixelMatrix::PixelMatrix(Vector2u size) : _size(size) {
        _pixelsTab = std::vector<Pixel>(x(_size) * y(_size), Pixel(0, 0, 0, 255));
    }


    PixelMatrix::~PixelMatrix() {}


    void PixelMatrix::setPixel(Vector2u pos, Pixel color) {
        if (x(pos) < x(_size) && y(pos) < y(_size))
            _pixelsTab[y(pos) * x(_size) + x(pos)] = color;
    }

    std::vector<Pixel> PixelMatrix::getPixelChar(Vector2u pos) {
        std::vector<Pixel> pixels = std::vector<Pixel>(6, Pixel(0, 0, 0, 255));
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 2; j++) {
                if (x(pos) + j < x(_size) && y(pos) + i < y(_size)) {
                    pixels[i * 2 + j] = _pixelsTab[(y(pos) + i) * x(_size) + x(pos) + j];
                }
            }
        return pixels;
    }

    void PixelMatrix::resize(Vector2u size) {
        _size = size;
        _pixelsTab.resize(x(_size) * y(_size), Pixel(0, 0, 0, 255));
    }

    void PixelMatrix::clear() {
        std::fill(_pixelsTab.begin(), _pixelsTab.end(), Pixel(0, 0, 0, 255));
    }

}