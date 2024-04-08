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
#include <csignal>
#include "SignalHandler.hpp"

Window::Window(std::string const title) : Window(title, "/dev/tty")
{
}

Window::Window(std::string const title, std::string const tty_path) {
    this->_title = title;
    this->_content = "";
    this->_tty_path = tty_path;
    this->_fd = open(_tty_path.c_str(), O_RDWR);
    struct winsize w;
    ioctl(_fd, TIOCGWINSZ, &w);
    if (w.ws_col == 0 || w.ws_row == 0)
        throw std::runtime_error("Can't get terminal size");

    int param = ioctl(_fd, F_GETFL, 0);
    fcntl(_fd, F_SETFL, param | O_NONBLOCK );
    _width = (w.ws_col + 1);
    _height = ((w.ws_row + 1) * 2);
    _pixels = std::vector<pixel_color>();
    _pixels.resize(_width * _height, pixel_color( 0, 0, 0,  255));
    _oldPixels = std::vector<pixel_color>();
    _oldPixels.resize(_width * _height, pixel_color( 0, 0, 0,  255));
    _clock = 60;
    SignalHandler::getInstance().registerWindow(this);
}


Window::~Window()
{
    SignalHandler::getInstance().unregisterWindow(this);
    close(_fd);
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
    for (u_int32_t i = 0; i < _height; i ++) {
        for (u_int32_t j = 0; j < _width; j++) {
            setPixel(j, i, pixel_color(0, 0,0,255));
        }
    }
}

void Window::moveCursor(u_int32_t y, u_int32_t x)
{
    _content += "\033[" + std::to_string(y / 2) + ";" + std::to_string(x) + "H";
}

void Window::printPixel()
{
    _content += std::string(reinterpret_cast<const char*>(u8"\u2584"));
}

void Window::setPixel(u_int32_t x, u_int32_t y, pixel_color color)
{
    if (x >= _width || y >= _height) {
        return;
    }
    _pixels[y * _width + x] = color;
}

void Window::alternateScreenBuffer()
{
    _content += "\033[?1049h";
}

void handleSignal(int signal)
{
    if (signal == SIGWINCH) {
    }
}

bool Window::updateTermSize()
{
    struct winsize w;
    w.ws_col = 0;
    w.ws_row = 0;
    ioctl(_fd, TIOCGWINSZ, &w);
    if (w.ws_col == 0 || w.ws_row == 0)
        return false;
    _width = (w.ws_col + 1);
    _height = ((w.ws_row + 1) * 2);

    _pixels.resize(_width * _height , pixel_color( 0, 0, 0,  255));
    _oldPixels.resize(_width * _height, pixel_color(0, 0, 0, 255));
    updateAllPixels();
    return true;
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
    for (u_int32_t i = 0; i < _height; i += 2) {
        for (u_int32_t j = 0; j < _width; j++) {
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
    for (u_int32_t i = 0; i < _height; i += 2) {
        for (u_int32_t j = 0; j < _width; j++) {
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
        for (u_int32_t i = 0; i < _height; i += 2) {
            for (u_int32_t j = 0; j < _width; j++) {
                _oldPixels[i * _width + j] = _pixels[i * _width + j];
                _oldPixels[(i + 1) * _width + j] = _pixels[(i + 1) * _width + j];
            }
        }
    }
    usleep(1000000 / _clock);
}

pixel_color Window::getPixelColor(u_int32_t x, u_int32_t y)
{
    return _pixels[y * _width + x];
}

pixel_color Window::getOldPixelColor(u_int32_t x, u_int32_t y)
{
    return _oldPixels[y * _width + x];
}
