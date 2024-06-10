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
#include "tdl/Text/Font/Font.hpp"
#include "tdl/Text/Text.hpp"
#include <tuple>
#include <queue>
#include "tdl/Matrix/Transform.hpp"
#include <chrono>
#include <fstream>

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    tdl::Window *win = tdl::Window::CreateWindow("bird");
    tdl::Texture *tex = tdl::Texture::createTexture("../example/assets/Spinner.png");
    tdl::Vector2u pos(10, 10);
    tdl::Sprite *sprite = tdl::Sprite::createSprite(tex, pos);
    tdl::RectU rect(0, 0, 32, 32);
    tex->setRect(rect);
    while (true)
    {
        win->clearPixel();
        sprite->draw(win);
        win->update();
        win->draw();
        for(tdl::Event event; win->pollEvent(event);) {
            if (event.type == tdl::Event::EventType::KeyPressed) {
                if (event.key.code == tdl::KeyCodes::KEY_ESC)
                    return 0;
                if (event.key.code == tdl::KeyCodes::KEY_RIGHT) {
                    pos += tdl::Vector2u(1, 0);
                }
                if (event.key.code == tdl::KeyCodes::KEY_LEFT) {
                    pos -= tdl::Vector2u(1, 0);
                }
                if (event.key.code == tdl::KeyCodes::KEY_UP) {
                    pos -= tdl::Vector2u(0, 1);
                }
                if (event.key.code == tdl::KeyCodes::KEY_DOWN) {
                    pos += tdl::Vector2u(0, 1);
                }
            }
        }
        sprite->setPosition(pos);
        if (rect.x() >= 32) {
            rect.x() = 0;
            if (rect.y() >= 96) {
                rect.y() = 0;
            } else {
                rect.y() += 32;
            }
        } else {
            rect.x() += 32;
        }
        win->printFrameRate();
        tex->setRect(rect);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::ofstream time_file("execution_time.txt", std::ios::app);
    time_file << elapsed.count() << std::endl;
    time_file.close();

    return 0;
}
