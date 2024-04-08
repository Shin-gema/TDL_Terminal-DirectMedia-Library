/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** window.hpp
*/

#ifndef LIBNCURSE_WINDOW_HPP
    #define LIBNCURSE_WINDOW_HPP

#include <string>
#include <list>
#include <array>
#include <vector>
#include <termios.h>

union pixel_color {
    u_int32_t color;
    struct {
        u_int8_t r;
        u_int8_t g;
        u_int8_t b;
        u_int8_t a;
    } __attribute__((packed));

    pixel_color() : color(0) {}
    pixel_color(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) : r(r), g(g), b(b), a(a) {}

    bool operator==(const pixel_color &other) const {
        return r == other.r && g == other.g && b == other.b && a == other.a;
    }

    bool operator!=(const pixel_color &other) const {
        return r != other.r || g != other.g || b != other.b || a != other.a;
    }
};

class Window {
    public:
        Window(std::string const title);
        Window(std::string const title, std::string const tty_path);
        ~Window();

        static void handleSignal(int sig);

        void setRGBFrontground(pixel_color color);
        void setRGBBackground(pixel_color color);
        void clearScreen();
        void clearPixel();
        void moveCursor(u_int32_t y, u_int32_t x);
        void printPixel();
        void setPixel(u_int32_t x, u_int32_t y, pixel_color color);
        bool updateTermSize();
        void create_window();
        void alternateScreenBuffer();
        void removeMouseCursor();
        void updateAllPixels();
        void update();
        void draw();

        [[nodiscard]] u_int32_t getHeight() const { return _height; }
        [[nodiscard]] u_int32_t getWidth() const { return _width; }
        pixel_color getPixelColor(u_int32_t x, u_int32_t y);
        pixel_color getOldPixelColor(u_int32_t x, u_int32_t y);
        int getFd() const { return _fd; }
        void disableEcho();

        [[nodiscard]] u_int8_t getFrameRate() const { return _clock; }
        void setFrameRate(u_int8_t clock) { _clock = clock; }

    private:

        struct termios _tty;
        std::string _tty_path = "/dev/tty";
        int _fd;
        u_int32_t _width;
        u_int32_t _height;
        u_int8_t _clock;
        std::string _title;
        std::string _content;
        std::vector<pixel_color> _pixels;
        std::vector<pixel_color> _oldPixels;

};

#endif //LIBNCURSE_WINDOW_HPP
