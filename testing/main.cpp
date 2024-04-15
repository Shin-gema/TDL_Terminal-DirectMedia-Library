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
#include "Vector.hpp"
#include "../logger/logger.hpp"
#include <png.h>
#include <tuple>
#include <queue>



int main()
{
    tdl::Window *win = tdl::Window::CreateWindow("test");
    tdl::Vector2u pos = tdl::Vector2u(10, 10);
    while (true)
    {
        win->clearPixel();
        for (tdl::Event event; win->pollEvent(event);){
            if (event.type == tdl::Event::EventType::KeyPressed){
                if (event.key.key == tdl::TDLKeyCodes::KEY_UP){
                    tdl::y(pos) -= 1;
                }
                if (event.key.key == tdl::TDLKeyCodes::KEY_DOWN){
                    tdl::y(pos) += 1;
                }
                if (event.key.key == tdl::TDLKeyCodes::KEY_LEFT){
                    tdl::x(pos) -= 1;
                }
                if (event.key.key == tdl::TDLKeyCodes::KEY_RIGHT){
                    tdl::x(pos) += 1;
                }
            }
        }
        win->setPixel(pos, tdl::Pixel(255, 0, 0, 255));
        win->update();
        win->draw();
    }
}
