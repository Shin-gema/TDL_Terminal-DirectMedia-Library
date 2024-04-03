/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** window.cpp
*/

#include "window.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <vector>
#include "../logger/logger.hpp"
#include <fcntl.h>
#include <termios.h>

Window::Window(std::string const title) {
    this->_title = title;
    this->_content = "";
    this->_fd = open("/dev/tty", O_RDWR);
    struct winsize w;
    ioctl(_fd, TIOCGWINSZ, &w);
    if (w.ws_col == 0 || w.ws_row == 0)
        throw std::runtime_error("Can't get terminal size");
    _width = w.ws_col + 1;
    _height = (w.ws_row + 1) * 2;
    _pixels = std::vector<pixel_color>();
    _pixels.resize(_width * _height, pixel_color( 0, 0, 0,  255));
    _oldPixels = std::vector<pixel_color>();
    _oldPixels.resize(_width * _height, pixel_color( 0, 0, 0,  255));
    _clock = 60;
    int param = ioctl(_fd, F_GETFL, 0);
    fcntl(_fd, F_SETFL, param | O_NONBLOCK);
}

Window::~Window()
{
}

void Window::setRGBFrontground(pixel_color color)
{
    _content += "\033[38;2;" + std::to_string(color.r) + ";" + std::to_string(color.g) + ";" + std::to_string(color.b) + "m";

}

void Window::setRGBBackground(pixel_color color)
{
    _content += "\033[48;2;" + std::to_string(color.r) + ";" + std::to_string(color.g) + ";" + std::to_string(color.b) + "m";
}

void Window::clearScreen()
{
    _content += "\033[2J";
}

void Window::clearPixel()
{
    for (u_int64_t i = 0; i < _height; i ++) {
        for (u_int64_t j = 0; j < _width; j++) {
            setPixel(j, i, pixel_color(0, 0,0,255));
        }
    }
}

void Window::moveCursor(u_int64_t y, u_int64_t x)
{
    _content += "\033[" + std::to_string(y / 2) + ";" + std::to_string(x) + "H";
}

void Window::printPixel()
{
    _content += u8"\u2584";
}

void Window::setPixel(u_int64_t x, u_int64_t y, pixel_color color)
{
    if (x > _width || y > _height)
        return;
    _pixels[y * _width + x] = color;
}

void Window::alternateScreenBuffer()
{
    _content += "\033[?1049h";
}

bool Window::updateTermSize()
{
    struct winsize w;
    ioctl(_fd, TIOCGWINSZ, &w);
    if (static_cast<u_int64_t>(w.ws_col) + 1!= _width || static_cast<u_int64_t>(w.ws_row + 1) * 2 != _height) {
        _width = w.ws_col + 1;
        _height = (w.ws_row + 1) * 2;
            _pixels.resize(_width * _height , pixel_color( 0, 0, 0,  255));
        _oldPixels.resize(_width * _height, pixel_color(0, 0, 0, 255));
        updateAllPixels();
        return true;
    };
    return false;
}

void Window::disableEcho()
{
    tcgetattr(_fd, &_tty);
    _tty.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&_tty);
}

void Window::create_window()
{
    updateAllPixels();
    draw();
}

void Window::removeMouseCursor()
{
    _content += "\033[?25l";
}

void Window::updateAllPixels()
{
    for (u_int64_t i = 0; i < _height; i += 2) {
        for (u_int64_t j = 0; j < _width; j++) {
            moveCursor(i, j);
            pixel_color pixelfront = _pixels[(i + 1) * _width + j];
            pixel_color pixelback = _pixels[i * _width + j];
            setRGBFrontground(pixelfront);
            setRGBBackground(pixelback);
            printPixel();
        }
    }
}

void Window::update()
{
    for (u_int64_t i = 0; i < _height; i += 2) {
        for (u_int64_t j = 0; j < _width; j++) {
            if (_pixels[i * _width + j].color != _oldPixels[i * _width + j].color
            || _pixels[(i + 1) * _width + j].color != _oldPixels[(i + 1) * _width + j].color){
                moveCursor(i, j);
                pixel_color pixelfront = _pixels[(i + 1) * _width + j];
                pixel_color pixelback = _pixels[i * _width + j];
                setRGBFrontground(pixelfront);
                setRGBBackground(pixelback);
                printPixel();
            }
        }
    }
}

void Window::draw()
{
    if (!_content.empty()) {
        write(_fd, _content.c_str(), _content.size());
        _content = "";
        for (u_int64_t i = 0; i < _height; i += 2) {
            for (u_int64_t j = 0; j < _width; j++) {
                _oldPixels[i * _width + j] = _pixels[i * _width + j];
                _oldPixels[(i + 1) * _width + j] = _pixels[(i + 1) * _width + j];
            }
        }
    }
    usleep(1000000 / _clock);
}

pixel_color Window::getPixelColor(u_int64_t x, u_int64_t y)
{
    return _pixels[y * _width + x];
}

pixel_color Window::getOldPixelColor(u_int64_t x, u_int64_t y)
{
    return _oldPixels[y * _width + x];
}