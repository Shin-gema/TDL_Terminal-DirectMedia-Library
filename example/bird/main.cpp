/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** main.cpp
*/

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include <tdl/Window/window.hpp>
#include "tdl/Event/Event.hpp"
#include "tdl/Input/inputKeyboard.hpp"
#include "tdl/Sprite/Sprite.hpp"
#include "tdl/Pixel/Pixel.hpp"
#include "tdl/Vector.hpp"
#include <tuple>
#include <queue>

int main()
{
    tdl::Window *win = tdl::Window::CreateWindow("bird");
    tdl::Texture *tex = tdl::Texture::createTexture("../example/assets/bird.png");
    tdl::Sprite *sprite = tdl::Sprite::createSprite(tex, tdl::Vector2u(0, 0));
    double rotation = 45.0;
    while (true)
    {
        tex->setScale(tdl::Vector2f(0.5, 0.5));
        sprite->setTexture(tex);
        win->clearPixel();
        sprite->drawOn(win);
        win->update();
        win->draw();
        for(tdl::Event event; win->pollEvent(event);) {
            if (event.type == tdl::Event::EventType::KeyPressed) {
                if (event.key.code == tdl::KeyCodes::KEY_ESC)
                    return 0;
            }
        }
        win->printFrameRate();
    }
}
