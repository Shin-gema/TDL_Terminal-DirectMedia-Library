#include "Window.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <vector>
#include <fcntl.h>
#include <termios.h>
#include <csignal>
#include "Window/windowBase.hpp"
#include "Signal/SignalHandler.hpp"

/**
 * @brief Construct a new tdl::Window::Window object
 * 
 * @param title The title of the window
 * @param tty_path The path to the tty to lauch the window, the available tty are /dev/tty or /dev/pts/0.../dev/pts/x
 * @note the SignalHandler.getInstance is used to register the window on the signal manager it permited to automatically resize the window when the terminal is resized
 */
tdl::Window::Window(std::string const title, std::string const ttyPath) :WindowBase(ttyPath), _title(title), _frameRate(60), _content("") {
    struct winsize w;
    int param = 0;
    _fd = open(ttyPath.c_str(), O_RDWR);
    if (_fd == -1)
        throw std::runtime_error("Can't open tty");
    ioctl(_fd, TIOCGWINSZ, &w);
    if (w.ws_col == 0 || w.ws_row == 0)
        throw std::runtime_error("Can't get terminal size");
    param = ioctl(_fd, F_GETFL, 0);
    fcntl(_fd, F_SETFL, param | O_NONBLOCK );
    _size = Vector2u((w.ws_col + 1), ((w.ws_row + 1) * 2));
    _pixelsTab = std::vector<Pixel>( x(_size) * y(_size), Pixel( 0, 0, 0,  255));
    _oldPixelsTab = std::vector<Pixel>(x(_size) * y(_size), Pixel( 0, 0, 0,  255));
    SignalHandler::getInstance().registerWindow(this);
}

/**
 * @brief Destroy the tdl::Window::Window object and unregister the window from the signal manager
 * 
 */
tdl::Window::~Window()
{
    SignalHandler::getInstance().unRegisterWindow(this);
    close(_fd);
}

/**
 * @brief Create a new Window object, initialize the window and return it
 * 
 * @param title the title of the window
 * @param tty_path the path to the tty to lauch the window, the available tty are /dev/tty or /dev/pts/0.../dev/pts/x
 * @return tdl::Window* 
 * @note this is only herre where the window constructor is called because it throw an error if the tty can't be open
 * also we initialize the window here that means that the black background should be printed on the terminal
 */
tdl::Window* tdl::Window::CreateWindow(std::string const title, std::string const ttyPath) {
    try {
        Window * win = new Window(title, ttyPath);
        win->disableEcho();
        win->removeMouseCursor();
        win->alternateScreenBuffer();
        win->update(true);
        win->draw();
        return win;
    } catch (std::runtime_error& e) {
        std::cerr << e.what();
        return nullptr;
    }
}


/**
 * @brief disable the echo of the terminal
 * we disable the echo of the terminal to avoid the input to be displayed on the terminal
 */
void tdl::Window::disableEcho()
{
    tcgetattr(_fd, &_tty);
    _tty.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&_tty);
}

/**
 * @brief write the content generate by updatePixel to the terminal
 * and save the current pixel to the old pixel table
 * @note the copy of the pixel in the oldpixel is make two at a time because 1 charactere = 2 pixel
 */
void tdl::Window::draw()
{
    if (!_content.empty()) {
        write(_fd, _content.c_str(), _content.size());
        _content = "";
        for (u_int32_t i = 0; i < y(_size); i += 2) {
            for (u_int32_t j = 0; j < x(_size); j++) {
                getOldPixel(Vector2u(j, i)) = getPixel(Vector2u(j, i));
                getOldPixel(Vector2u(j, i + 1))= _pixelsTab[(i + 1) * x(_size) + j];
            }
        }
    }
    usleep(1000000 / _frameRate);
}