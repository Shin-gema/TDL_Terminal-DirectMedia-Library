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
#include "Pixel/Pixel.hpp"
#include "Vector.hpp"
#include "Window/windowBase.hpp"

namespace tdl {
    class Window : public WindowBase {
        
        public:
            static Window* CreateWindow(std::string const title, std::string const ttyPath = "/dev/tty");
            ~Window();

            // pixel management
            void clearPixel();
            void setPixel(Vector2u pos, Pixel color);
            void update(bool all = false);
            void draw();

            // getter and setter
            [[nodiscard]] u_int32_t getHeight() { return y(_size); }
            [[nodiscard]] u_int32_t getWidth() { return x(_size); }
            [[nodiscard]] Pixel &getPixel(Vector2u pos);
            [[nodiscard]] Pixel &getOldPixel(Vector2u pos);
            [[nodiscard]] u_int8_t getFrameRate() const { return _frameRate; }

            void setFrameRate(u_int8_t frameRate) { _frameRate = frameRate; }

            void updateTermSize();
        private:
            Window(std::string const title, std::string const ttyPath);

            // tty management
            void disableEcho();

            // ansii escape codes generation function
            void setRGBFrontGround(Pixel color);
            void setRGBBackGround(Pixel color);
            void clearScreen();
            void moveCursor(Vector2u pos);
            void printPixel();
            void alternateScreenBuffer();
            void removeMouseCursor();

            std::string _title;
            u_int8_t _frameRate;
            std::string _content;
            Vector2u _size;
            struct termios _tty;
            std::vector<Pixel> _pixelsTab;
            std::vector<Pixel> _oldPixelsTab;

    };
}

#endif //LIBNCURSE_WINDOW_HPP
