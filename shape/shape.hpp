/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** shape.hpp
*/

#ifndef LIBNCURSE_SHAPE_HPP
    #define LIBNCURSE_SHAPE_HPP

#include "../window/window.hpp"

enum MoveVector {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

class Square {
public:
    void draw(Window *win);
    void move(Window *win);
    void setPos(int x, int y);
    void setColor(int color);
    void setSize(int size);
    void setVector(MoveVector vector) { _vector = vector; }
private:
    int _x;
    int _y;
    int _size;
    pixel_color _color;
    MoveVector _vector = NONE;
};

#endif //LIBNCURSE_SHAPE_HPP
