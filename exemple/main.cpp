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
#include "../include/Pixel/Pixel.hpp"
#include "Vector.hpp"
#include <png.h>
#include <tuple>
#include <queue>

int main()
{
    tdl::Window *win = tdl::Window::CreateWindow("test");
    tdl::Texture *tex = tdl::Texture::createTexture("./exemple/Spinner.png", tdl::Vector2f(1.0, 1.0 ), false);
    tdl::Vector2u pos = tdl::Vector2u(20, 20);
    tdl::RectU rect = tdl::RectU(20, 20, 100, 100);
    tdl::RectU trect = tdl::RectU(0, 0, 32, 32);
    tdl::Sprite *sprite = tdl::Sprite::createSprite(tex, pos, rect);
    tex->setRect(trect);
    double rotation = 45.0;
    while (true)
    {
        win->clearPixel();
        sprite->drawOn(win);
        win->update();
        win->draw();
        for(tdl::Event event; win->pollEvent(event);)
        {
            if (event.type == tdl::Event::EventType::KeyPressed)
            {
                if( event.key.code == tdl::TDLKeyCodes::KEY_ENTER)
                    return 0;
            }
        }
        if (tdl::x(trect) >= 32) {
            trect = tdl::RectU(0,tdl::y(trect), 32, 32);
            if (tdl::y(trect) > 64)
                trect = tdl::RectU(0, 0, 32, 32);
            else
                trect = tdl::RectU(0, tdl::y(trect) + 32, 32, 32);
        } else {
            trect = tdl::RectU(tdl::x(trect) + 32, tdl::y(trect), 32, 32);
        }
        tex->setRect(trect);
        //sprite->setRotation(rotation);
    }
}
