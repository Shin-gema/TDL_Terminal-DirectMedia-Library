#include "tdl/Window.hpp"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <map>

/**
 * @brief reset the pixel table of the window with black pixel
 * 
 */
void tdl::Window::clearPixel()
{
    if (getUpdate()) {
        getMatrix().clear();
        setUpdate(false);
    }
}

void tdl::Window::updateTermSize()
{
    struct winsize w{};
    int timeout = 10;
    w.ws_col = 0;
    w.ws_row = 0;
    while (w.ws_col == 0 && w.ws_row == 0 && timeout > 0) {
        ioctl(_fd, TIOCGWINSZ, &w);
        timeout--;
    }
    _size = Vector2u((w.ws_col + 1) * 2, ((w.ws_row + 1) * 3));
    getMatrix().resize(_size);
    getOldMatrix().resize(_size);
    update(true);
}

void tdl::Window::update(bool all) {
    CharColor charColor;
    Vector2u pos = Vector2u(0, 0);
    Vector2u oldPos = Vector2u(0, 0);
    Pixel pixels[6] = {Pixel(0, 0, 0, 0)};
    Pixel oldForeColor = Pixel(0, 0, 0, 0);
    Pixel oldBackColor = Pixel(0, 0, 0, 0);

    if (_update)
        _update = false;
    setUpdate(true);
    for (u_int32_t i = 0; i < _size.y(); i += 3) {
        for (u_int32_t j = 0; j < _size.x(); j += 2) {
            try {
                getMatrix().getPixelChar(Vector2u(j, i), pixels);
            } catch (std::out_of_range &e) {
                continue;
            }
            getOldMatrix().setPixelChar(Vector2u(j, i), pixels);
            charColor = getMatrix().computeCharColor(Vector2u(j, i), pixels);
            if (!charColor.shape)
                continue;
            if (pos.x() != oldPos.x() + 2) {
                moveCursor(pos);
            }
            if (charColor.ForeGround != oldForeColor) {
                setRGBFrontGround(charColor.ForeGround);
                oldForeColor = charColor.ForeGround;
            }
            if ((charColor.BackGround != oldBackColor)) {
                setRGBBackGround(charColor.BackGround);
                oldBackColor = charColor.BackGround;
            }
            printPixel(charColor.shape);
            oldPos = pos;
            pos.x() += 2;
        }
        pos.x() = 0;
        pos.y() += 2;
    }
}
