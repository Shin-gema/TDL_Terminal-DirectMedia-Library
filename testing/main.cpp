/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** main.cpp
*/

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../include/Window/window.hpp"
#include "../include/Event/Event.hpp"
#include "../include/Input/inputKeyboard.hpp"
#include "../include/Sprite/Sprite.hpp"
#include "Vector.hpp"
#include "../logger/logger.hpp"
#include <png.h>
#include <tuple>
#include <queue>



int main()
{
    tdl::Window *win = tdl::Window::CreateWindow("test");
    tdl::Texture *tex = tdl::Texture::createTexture("./testing/Spinner.png", tdl::Vector2f(1.5,1.5));
    tdl::Vector2u pos = tdl::Vector2u(10, 10);
    tdl::RectU rect = tdl::RectU(0, 0, 16, 16);
    tdl::Sprite *sprite = new tdl::Sprite(tex, pos, rect);

    while (true)
    {
        win->clearPixel();
        sprite->setRect(rect);
        sprite->drawOn(win);
        win->update();
        win->draw();
        if (tdl::x(rect) >= 32 + 16) {
            rect = tdl::RectU(0, tdl::y(rect), 32 + 16, 32 + 16);
            if (tdl::y(rect) >= 96 + 16) {
                rect = tdl::RectU(0, 0, 32 + 16, 32 + 16);
            } else {
                rect = tdl::RectU(tdl::x(rect), tdl::y(rect) + 32 + 16, 32 + 16, 32 + 16);
            }
        } else {
            rect = tdl::RectU(tdl::x(rect) + 32 + 16, tdl::y(rect), 32 + 16, 32 + 16);
        }
    }
}
