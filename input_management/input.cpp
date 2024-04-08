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
#include <vector>


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

std::vector<NCursesKeyCodes> keysList = {
    KEY_UP,
    KEY_DOWN,
    KEY_RIGHT,
    KEY_LEFT,
    KEY_SPACE,
    KEY_ENTER,
    KEY_ESC,
    KEY_BACKSPACE,
    KEY_TAB,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_0,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_END,
};