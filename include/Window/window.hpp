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
#include "Matrix/PixelMatrix.hpp"

namespace tdl {


    struct CharColor {
        const char *shape;
        Pixel ForeGround;
        Pixel BackGround;
    };

    class Window : public WindowBase {
        
        public:
            static Window* CreateWindow(std::string const title, std::string const ttyPath = "/dev/tty");
            ~Window();

            // pixel management
            void clearPixel();
            CharColor computeCharColor(Vector2u pos);
            void update(bool all = false);
            void draw();

            // getter and setter
            [[nodiscard]] u_int32_t getHeight() { return y(_size); }
            [[nodiscard]] u_int32_t getWidth() { return x(_size); }
            [[nodiscard]] u_int8_t getFrameRate() const { return _frameRate; }
            [[nodiscard]] PixelMatrix &getPixelsTab() { return _pixelsTab;}
            [[nodiscard]] PixelMatrix &getOldPixelsTab() { return _oldPixelsTab; }

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
            void printPixel(const char *shape);
            void alternateScreenBuffer();
            void removeMouseCursor();

            std::string _title;
            u_int8_t _frameRate = 60;
            std::string _content;
            Vector2u _size;
            struct termios _tty;
            PixelMatrix _pixelsTab;
            PixelMatrix _oldPixelsTab;

    };
}

#endif //LIBNCURSE_WINDOW_HPP
