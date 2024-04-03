/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** main.cpp
*/

#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../window/window.hpp"
#include "../texture/texture.hpp"
#include "../input_management/input.hpp"
#include "../logger/logger.hpp"
#include <png.h>
#include <tuple>

void setAnimeTexture(Texture *texture)
{
    textureRect rect = texture->getRect().value();
    if (rect.x + 32 < texture->getWidth() - 32)
        rect.x += 32;
    else {
        rect.x = 0;
        if (rect.y + 32 < texture->getHeight())
            rect.y += 32;
        else
            rect.y = 0;
    }
    texture->setTextureRect(rect);
}

void textureBouncWall(Texture *texture, Window *win) {

    Input input = Input();
    int x = 50;
    int y = 50;
    float i = 0.0;
    while (1) {
        input.readInput(win);
        if (input.on_pressed(KEY_ESC))
            break;
        win->updateTermSize();
        win->clearPixel();
        if (input.on_pressed(KEY_D))
            x += 1;
        if (input.on_pressed(KEY_Q))
            x -= 1;
        if (input.on_pressed(KEY_Z))
            y -= 1;
        if (input.on_pressed(KEY_S))
            y += 1;
        texture->rotate(i);
        i += 1;
        if (i > 360)
            i = 0;
        texture->draw(win);
        win->update();
        win->draw();
    }
}

int main()
{
    Window win("test");
    Texture texture("./testing/Spinner.png");
    texture.setPos(0, 0);
    win.disableEcho();
    win.removeMouseCursor();
    win.alternateScreenBuffer();
    win.create_window();
    textureBouncWall(&texture, &win);
    return 0;
}
