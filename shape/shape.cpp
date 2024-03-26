/*
** EPITECH PROJECT, 2024
** libNcurse
** File description:
** shape.cpp
*/

#include "shape.hpp"
#include "../window/window.hpp"

void Square::draw(Window *win)
{
    if (_vector == DOWN){
        for (u_int64_t y = _y == 0 ? _y : _y - 1 ; y < _y + _size; y++) {
            for (u_int64_t x = _x; x < _x + _size; x++) {
                if (x < win->getWidth() && y > 0)
                    win->setPixel(x, y, _color);
                else
                    win->setPixel(x, y, win->getOldPixelColor(x, y));
            }
        }
        return;
    }
    if (_vector == UP){
        for (u_int64_t y = _y; y < _y + _size + 1; y++) {
            for (u_int64_t x = _x; x < _x + _size; x++) {
                if (x < win->getWidth() && y < _y + _size)
                    win->setPixel(x, y, _color);
                else
                    win->setPixel(x, y, win->getOldPixelColor(x, y));
            }
        }
        return;
    }
    if (_vector == LEFT){
        for (u_int64_t y = _y; y < _y + _size; y++) {
            for (u_int64_t x = _x; x < _x + _size + 1; x++) {
                if (x < _x + _size && y < _y + _size)
                    win->setPixel(x, y, _color);
                else
                    win->setPixel(x, y, win->getOldPixelColor(x, y));
            }
        }
        return;
    }
    if (_vector == RIGHT){
        for (u_int64_t y = _y;  y < _y + _size; y++) {
            for (u_int64_t i = _x - 1 ; i < _x + _size; i++) {
                if(i >= _x)
                    win->setPixel(i, y, _color);
                else
                    win->setPixel(i, y, win->getOldPixelColor(i, y));
            }
        }
        return;
    }
    int tmpY = _y;
    int tmpX = _x;

    if (tmpY + _size > win->getHeigth())
        tmpY = win->getHeigth() - _size;
    if (tmpX + _size> win->getWidth())
        tmpX = win->getWidth() - _size;
    for (u_int64_t y = tmpY; y < tmpY + _size; y++) {
        for (u_int64_t x = tmpX; x < tmpX + _size; x++) {
            if (x < win->getWidth() && y < win->getHeigth())
                win->setPixel(x, y, _color);
        }
    }
}

void Square::move(Window *win)
{
    switch (_vector) {
        case UP:
            if (_y > 0)
                _y--;
            else
                _y = 0;
            break;
        case DOWN:
            if (_y + _size < win->getHeigth())
                _y++;
            else
                _y = win->getHeigth() - _size;
            break;
        case LEFT:
            if (_x > 0)
                _x--;
            else
                _x = 0;
            break;
        case RIGHT:
            if (_x + _size < win->getWidth())
                _x++;
            else
                _x = win->getWidth() - _size;
            break;
        default:
            break;
    }

}

void Square::setPos(int x, int y)
{
    _x = x;
    _y = y;
}

void Square::setColor(int color)
{
    _color.color = color;
}

void Square::setSize(int size)
{
    _size = size;
}