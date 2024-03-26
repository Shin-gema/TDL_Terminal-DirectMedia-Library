/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** input.cpp
*/

#include "input.hpp"
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include "../logger/logger.hpp"
#include "../window/window.hpp"
#include <chrono>


Input::Input()
{
    _shared_data = 0;
}

Input::~Input()
{
}

void Input::readInput(Window *win) {
    int _nread = 0;
    ioctl(win->getFd(), FIONREAD, &_nread);
    char buffer[_nread];
    std::chrono::steady_clock::time_point key_pressed_time;
    std::chrono::steady_clock::time_point key_maintained_time;
    LOG("KEY PRESSED TIME: " + std::to_string(key_pressed_time.time_since_epoch().count()));
    ssize_t bytesRead = read(win->getFd(), buffer, _nread);
    if (_nread != 0) {
        if (buffer[0] == 27 && buffer[1] == 91) {
            switch (buffer[2]) {
                case 65:
                    _shared_data = KEY_UP;
                    break;
                case 66:
                    _shared_data = KEY_DOWN;
                    break;
                case 67:
                    _shared_data = KEY_RIGHT;
                    break;
                case 68:
                    _shared_data = KEY_LEFT;
                    break;
                default:
                    _shared_data = buffer[2];
                    break;
            }
        } else {
            _shared_data = buffer[0];
        }
        if (_key_states[_shared_data]) {
            if (!_prev_key_states[_shared_data]) {
                key_pressed_time = std::chrono::steady_clock::now();
            } else {
                key_maintained_time = std::chrono::steady_clock::now();
                std::chrono::duration<double> delay = key_maintained_time - key_pressed_time;
                if (delay.count() < 0.5) {
                    _key_states[_shared_data] = true;
                }
                LOG("Delay: " + std::to_string(delay.count()));
            }
        }
        _key_states[_shared_data] = true;
    } else {
        for (auto &key: _key_states) {
            if (key.second) {
                _prev_key_states[key.first] = true;
                key.second = false;
            } else {
                _prev_key_states[key.first] = false;
            }
        }
    }
}

char Input::getKeyCode() {
    char key_code = _shared_data;
    _shared_data = 0;
    return key_code;
}

bool Input::on_pressed(char key)
{
    return _key_states[key] && !_prev_key_states[key];
}

bool Input::on_maintain(char key)
{
    return _key_states[key];
}

bool Input::on_release(char key)
{
    return !_key_states[key] && _prev_key_states[key];
}