#include "tdl/Window.hpp"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <map>

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

/**
 * @brief reset the pixel table of the window with black pixel
 * 
 */
void tdl::Window::clearPixel()
{
    _pixelsTab.clear();
}

/**
 * @brief update the terminal size
 * @warning this function is called at the creation of the window and when the terminal size change
 * by the signale handler 
 */
void tdl::Window::updateTermSize()
{
    struct winsize w;
    int timeout = 10;
    w.ws_col = 0;
    w.ws_row = 0;
    while (w.ws_col == 0 && w.ws_row == 0 && timeout > 0) {
        ioctl(_fd, TIOCGWINSZ, &w);
        timeout--;
    }
    _size = Vector2u((w.ws_col + 1) * 2, ((w.ws_row + 1) * 3));
    _pixelsTab.resize(_size);
    _oldPixelsTab.resize(_size);
    update(true);
}

/**
 * @brief compute the color of the char at the position pos
 * 
 * @param pos the position of the char
 * @return CharColor the color of the char
 */
tdl::CharColor tdl::Window::computeCharColor(Vector2u pos, std::vector<Pixel> pixels)
{
    CharColor charColor;

    std::map<Pixel, int> colorCounts;
    std::map<Pixel, std::vector<std::pair<int, int>>> pixelGroups;

    for (int y = 0; y < 3; ++y) {
        for (int x = 0; x < 2; ++x) {
            Pixel pixel = pixels[y * 2 + x];
            colorCounts[pixel]++;
            pixelGroups[pixel].push_back({y, x});
        }
    }

    Pixel mostPresentColor1, mostPresentColor2;
    int maxCount1 = 0, maxCount2 = 0;
    for (const auto& pair : colorCounts) {
        if (pair.second > maxCount1) {
            mostPresentColor2 = mostPresentColor1;
            maxCount2 = maxCount1;
            mostPresentColor1 = pair.first;
            maxCount1 = pair.second;
        } else if (pair.second > maxCount2) {
            mostPresentColor2 = pair.first;
            maxCount2 = pair.second;
        }
    }
    charColor.ForeGround = mostPresentColor1;
    charColor.BackGround = mostPresentColor2;
    charColor.shape = PixelCharMap[pixelGroups[mostPresentColor1]];
    return charColor;
}

/**
 * @brief update the window with the new pixel to draw on the screen by generating an optimized ansii escape code sequence
 * 
 * @param all an boolean to force the update of all the pixel
 * @note if all is true the optimisation will be skip and all the screen is generated it will be useful at the start of an window or if you want to clear it to black
 */
void tdl::Window::update(bool all) {
    CharColor charColor;
    Vector2u pos = Vector2u(0, 0);
    Vector2u oldPos = Vector2u(0, 0);
    std::vector<Pixel> pixels;
    Pixel oldForeColor = Pixel(0, 0, 0, 0);
    Pixel oldBackColor = Pixel(0, 0, 0, 0);
    if (!all) {
        for (Vector2u p = _changedPixels.front(); !_changedPixels.empty(); p = _changedPixels.front()) {
            if (x(p) >= getWidth() || y(p) >= getHeight()) {
                _changedPixels.pop();
                continue;
            }
            pixels = _pixelsTab.getPixelChar(p);
            charColor = computeCharColor(p, pixels);
            moveCursor(p);
            if (charColor.ForeGround != oldForeColor) {
                setRGBFrontGround(charColor.ForeGround);
                oldForeColor = charColor.ForeGround;
            }
            if (charColor.BackGround != oldBackColor) {
                setRGBBackGround(charColor.BackGround);
                oldBackColor = charColor.BackGround;
            }
            printPixel(charColor.shape);
            _changedPixels.pop();
        }
    } else {
        for (u_int32_t i = 0; i < y(_size); i += 3) {
            for (u_int32_t j = 0; j < x(_size); j += 2) {
                pixels = _pixelsTab.getPixelChar(Vector2u(j, i));
                charColor = computeCharColor(Vector2u(j, i), pixels);
                if (pos != oldPos + Vector2u(2, 0)) {
                    moveCursor(pos);
                }
                if (charColor.ForeGround != oldForeColor) {
                    setRGBFrontGround(charColor.ForeGround);
                    oldForeColor = charColor.ForeGround;
                }
                if (charColor.BackGround != oldBackColor) {
                    setRGBBackGround(charColor.BackGround);
                    oldBackColor = charColor.BackGround;
                }
                printPixel(charColor.shape);
                pos += Vector2u(1, 0);
                oldPos = pos;
            }
            pos = Vector2u(0, y(pos) + 2);
        }
    }
}
