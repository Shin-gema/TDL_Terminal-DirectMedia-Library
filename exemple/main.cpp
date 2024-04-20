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
#include <png.h>
#include <tuple>
#include <queue>



int main()
{
    tdl::Window *win = tdl::Window::CreateWindow("test");
    tdl::Texture *tex = tdl::Texture::createTexture("./exemple/Spinner.png", tdl::Vector2f(1.0, 1.0), true);
    tdl::Vector2u pos = tdl::Vector2u(0, 0);
    tdl::RectU rect = tdl::RectU(0, 0, 100, 100);
    tdl::RectU textRect = tdl::RectU(0, 0, 32, 32);
    tdl::Sprite *sprite = tdl::Sprite::createSprite(tex, pos, rect);
    tex->setRect(textRect);
    //sprite->setTint(tdl::Pixel(0, 255, 0, 100));

    double rotation = 0;
    while (true)
    {
        win->clearPixel();
        tex->setRect(textRect);
        sprite->setRotation(rotation);
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
        if (tdl::x(textRect) >= 32 ) {
            textRect = tdl::RectU(0, tdl::y(textRect), 32, 32);
            if (tdl::y(textRect) >= 96) {
                textRect = tdl::RectU(0, 0, 32, 32);
            } else {
                textRect = tdl::RectU(tdl::x(textRect), tdl::y(textRect) + 32, 32, 32);
            }
        } else {
            textRect = tdl::RectU(tdl::x(textRect) + 32, tdl::y(textRect), 32, 32);
        }
        rotation += 1;
    }
}
