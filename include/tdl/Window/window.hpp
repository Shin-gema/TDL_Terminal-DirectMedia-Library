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
#include <iostream>
#include <array>
#include <vector>
#include <termios.h>
#include "tdl/Pixel/Pixel.hpp"
#include "tdl/Vector.hpp"
#include "tdl/Window/windowBase.hpp"
#include "tdl/Matrix/PixelMatrix.hpp"
#include "tdl/Drawable/Drawable.hpp"

namespace tdl {

    class Window : public WindowBase , public Drawable {
        
        public:
            static Window* CreateWindow(std::string const& title, std::string const& ttyPath = "/dev/tty");
            ~Window();

            // pixel management
            void clearPixel();

            void update(bool all = false);
            void draw();

            // getter and setter
            [[nodiscard]] u_int32_t getHeight() { return _size.y(); }
            [[nodiscard]] u_int32_t getWidth() { return _size.x(); }
            [[nodiscard]] u_int8_t getFrameRate() const { return _frameRate; }

            void setFrameRate(u_int8_t frameRate) { _frameRate = frameRate; }

            void updateTermSize();

            void printFrameRate();

            void registerUpdate(Vector2u pos);

        private:
            Window(std::string  title, std::string const& ttyPath);

            // tty management
            void disableEcho();

            // ansii escape codes generation function
            void setRGBFrontGround(Pixel color);
            void setRGBBackGround(Pixel color);
            void clearScreen();
            void moveCursor(Vector2u pos);
            void printPixel(const char *shape);
            void alternateScreenBuffer();
            void removeMouseCursor();

            void draw(Drawable *drawable) { return; }

            std::string _title;
            u_int8_t _frameRate = 60;
            std::string _content;
            Vector2u _size;
            struct termios _tty{};
            bool _update = true;

            int framecounter = 0;
            std::chrono::time_point<std::chrono::system_clock> start;

    };
}

#endif //LIBNCURSE_WINDOW_HPP
