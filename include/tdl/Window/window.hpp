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
    /**
     * @class Window
     * @brief Window class
     */
    class Window : public WindowBase , public Drawable {
        
        public:

        /**
         * @brief Create a Window object
         * 
         * @param title the title of the window
         * @param ttyPath the path to the tty by default it's /dev/tty
         * @return Window* a pointer to the window
         */
            static Window* CreateWindow(std::string const& title, std::string const& ttyPath = "/dev/tty");

        /**
         * @brief Destroy the Window object
         * 
         */
            ~Window();

        /**
         * @brief clear the pixel matrix
         * 
         */
            void clearPixel();

        /**
         * @brief update the window with the new pixel to draw on the screen by generating an optimized ansii escape code sequence
         * 
         * @param all an boolean to force the update of all the pixel
         * @note if all is true the optimisation will be skip and all the screen is generated it will be useful at the start of an window or if you want to clear it to black
         */
            void update(bool all = false);

        /**
         * @brief write the content generate by updatePixel to the terminal
         * and save the current pixel to the old pixel table
         * @note the copy of the pixel in the oldpixel is make two at a time because 1 charactere = 2 pixel
         */
            void draw();

        /**
         * @brief Get the Height object
         * 
         * @return u_int32_t the height of the window
         */
            [[nodiscard]] u_int32_t getHeight() { return _size.y(); }

        /**
         * @brief Get the Width object
         * 
         * @return u_int32_t the width of the window
         */
            [[nodiscard]] u_int32_t getWidth() { return _size.x(); }

        /**
         * @brief Get the Frame Rate object
         * 
         * @return u_int8_t the frame rate of the window
         */
            [[nodiscard]] u_int8_t getFrameRate() const { return _frameRate; }

        /**
         * @brief Set the Frame Rate object
         * 
         * @param frameRate the new frame rate
         */
            void setFrameRate(u_int8_t frameRate) { _frameRate = frameRate; }

        /**
         * @brief update the terminal size
         * @warning this function is called at the creation of the window and when the terminal size change
         * by the signale handler 
         */
            void updateTermSize();

        /**
         * @brief print the frame rate on the terminal
         * 
         */
            void printFrameRate();

        /**
         * @brief register the update of the pixel at the position pos
         * 
         * @param pos the position of the pixel to update
         */
            void registerUpdate(Vector2u pos);

        private:

        /**
         * @brief Construct a new tdl::Window::Window object
         * 
         * @param title The title of the window
         * @param tty_path The path to the tty to lauch the window, the available tty are /dev/tty or /dev/pts/0.../dev/pts/x
         * @note the SignalHandler.getInstance is used to register the window on the signal manager it permited to automatically resize the window when the terminal is resized
         */
            Window(std::string  title, std::string const& ttyPath);

        /**
         * @brief disable the echo of the terminal
         * we disable the echo of the terminal to avoid the input to be displayed on the terminal
         */
            void disableEcho();

        /**
         * @brief ansii front color code
         * 
         * @param pixel the pixel to get the color
         */
            void setRGBFrontGround(Pixel color);

        /**
         * @brief ansii back color code
         * 
         * @param pixel the pixel to get the color
         */
            void setRGBBackGround(Pixel color);

        /**
         * @brief ansii clear screen code
         * 
         */
            void clearScreen();
 
        /**
         * @brief ansii move cursor code
         * 
         * @param pos the position to move the cursor
         */
            void moveCursor(Vector2u pos);

        /**
         * @brief ansii print pixel code
         * 
         */
            void printPixel(const char *shape);

        /**
         * @brief ansii alternate screen buffer code
         * 
         */   
            void alternateScreenBuffer();

        /**
         * @brief ansii remove mouse cursor code
         * 
         */
            void removeMouseCursor();

            void draw(Drawable *drawable) { return; }

            std::string _title; /* !< the title of the window */
            u_int8_t _frameRate = 60; /* !< the frame rate of the window */
            std::string _content; /* !< the content of the window */
            Vector2u _size; /* !< the size of the window */
            struct termios _tty{}; /* !< the terminal configuration */
            bool _update = true; /* !< a boolean to check if the window need to be updated */

            int framecounter = 0; /* !< the frame counter */
            std::chrono::time_point<std::chrono::system_clock> start; /* !< the start time of the frame */
    };
}

#endif //LIBNCURSE_WINDOW_HPP
