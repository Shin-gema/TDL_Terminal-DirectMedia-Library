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

void textureBouncWall(Texture *texture, Window *win) {

    Input input = Input();

    u_int64_t x = 1;
    u_int64_t y = 1;
    MoveVector vectorWidth = RIGHT;
    MoveVector vectorHeight = DOWN;
    pixel_color color = {.r = 0, .g = 0, .b = 0, .a = 100};
    while (1) {
        win->updateTermSize();
        win->clearPixel();
        //win->clearScreen();
        texture->draw(win);
        if (vectorWidth == RIGHT)
            x++;
        else
            x--;
        if (vectorHeight == DOWN)
            y++;
        else
            y--;
        if (x + texture->getWidthResized().value() >= win->getWidth()) {
            vectorWidth = LEFT;
            color.color += 10000;
        }
        if (x == 0) {
            color.color += 10000;
            vectorWidth = RIGHT;
        }
        if (y + texture->getHeightResized().value() >= win->getHeigth()) {
            color.color += 10000;
            vectorHeight = UP;
        }
        if (y == 0) {
            color.color += 10000;
            vectorHeight = DOWN;
        }
        input.readInput(win);
        if (input.on_maintain(KEY_C))
            texture->setTint({.r = 0, .g = 255, .b = 0, .a = 255});
        if (input.on_release(KEY_C))
            texture->resetTintColor();
        texture->setPos(x, y);
        win->update();
        win->draw();
    }

}

int main()
{
    Window win("test");
    Texture texture("./testing/dvd.png");
    texture.resizeImage(0.1);
    win.disableEcho();
    win.removeMouseCursor();
    win.alternateScreenBuffer();
    win.create_window();
    textureBouncWall(&texture, &win);
    return 0;
}
