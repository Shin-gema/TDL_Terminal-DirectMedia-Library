#include "Window.hpp"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>

/**
 * @brief reset the pixel table of the window with black pixel
 * 
 */
void tdl::Window::clearPixel()
{
    for (u_int32_t i = 0; i < y(_size); i ++) {
        for (u_int32_t j = 0; j < x(_size); j++) {
            setPixel(Vector2u(j, i), Pixel(0, 0,0, 255));
        }
    }
}

/**
 * @brief set Pixel color at the position x, y
 * 
 * @param x the x position of the pixel
 * @param y the y position of the pixel
 * @param color the color of the pixel
 * @warning if the position is out of range the function will print an error message and nothing will be done
 */
void tdl::Window::setPixel(Vector2u pos, Pixel color)
{
    if (x(pos) >= x(_size) || y(pos) >= y(_size)) {
        return;
    }
    getPixel(pos) = color;
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
    _size = Vector2u((w.ws_col + 1), ((w.ws_row + 1) * 2));
    _pixelsTab.resize(x(_size) * y(_size) , Pixel( 0, 0, 0,  255));
    _oldPixelsTab.resize(x(_size) * y(_size), Pixel(0, 0, 0, 255));
    update(true);
}

/**
 * @brief update the window with the new pixel to draw on the screen by generating an optimized ansii escape code sequence
 * 
 * @param all an boolean to force the update of all the pixel
 * @note if all is true the optimisation will be skip and all the screen is generated it will be useful at the start of an window or if you want to clear it to black
 */
void tdl::Window::update(bool all)
{
    for (u_int32_t i = 0; i < y(_size); i += 2) {
        for (u_int32_t j = 0; j < x(_size); j++) {
            if (getPixel(Vector2u(j, i)).color != getOldPixel(Vector2u(j, i)).color || getPixel(Vector2u(j, i + 1)).color != getOldPixel(Vector2u(j, i + 1)).color || all == true) {
                moveCursor(Vector2u(j, i));
                Pixel oldPixelFront = getOldPixel(Vector2u(j, i + 1));
                Pixel oldPixelBack = getOldPixel(Vector2u(j, i));
                setRGBFrontGround(oldPixelFront + getPixel(Vector2u(j, i + 1)));
                setRGBBackGround(oldPixelBack + getPixel(Vector2u(j, i)));
                printPixel();
            }
        }
    }
}

/**
 * @brief getter for the pixel tab
 * 
 * @param pos the position of the pixel
 * @return tdl::Pixel the pixel at the position pos
 */
tdl::Pixel &tdl::Window::getPixel(Vector2u pos)
{
    return _pixelsTab[y(pos) * x(_size) + x(pos)];
}

/**
 * @brief getter for the old pixel tab
 * 
 * @param pos the position of the pixel
 * @return tdl::Pixel the old pixel at the position pos
 */
tdl::Pixel &tdl::Window::getOldPixel(Vector2u pos)
{
    return _oldPixelsTab[y(pos) * x(_size) + x(pos)];
}
