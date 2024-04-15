/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** input.cpp
*/

#include "Input/inputKeyboard.hpp"
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <termios.h>
#include "../logger/logger.hpp"
#include "Window/windowBase.hpp"
#include <vector>


tdl::InputKeyboard::InputKeyboard()
{
}

tdl::InputKeyboard::~InputKeyboard()
{
}

/**
 * @brief Read the input from the keyboard and push the event in the window event queue
 * 
 * @param win 
 */
void tdl::InputKeyboard::readInputKeyboard(WindowBase *win) {
    int _nread = 0;
    ioctl(win->getFd(), FIONREAD, &_nread);
    char buffer[_nread];
    read(win->getFd(), buffer, _nread);
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
                    _shared_data = charToKeyCodes(buffer[2]);
                    break;
            }
        } else {
            _shared_data = charToKeyCodes(buffer[0]);
        }
        _key_states[_shared_data] = true;
        Event event;
        event.type = Event::EventType::KeyPressed;
        event.key.key = _shared_data;
        win->pushEvent(event);
    } else {
        for (auto &key: _key_states) {
            if (key.second) {
                _prev_key_states[key.first] = true;
                key.second = false;
                Event event;
                event.type = Event::EventType::KeyReleased;
                event.key.key = charToKeyCodes(key.first);
                win->pushEvent(event);
            } else {
                _prev_key_states[key.first] = false;
            }
        }
    }
}

/**
 * @brief return a cast between a char and a TDLKeyCodes
 * 
 * @param key the char to cast
 * @return tdl::TDLKeyCodes the casted value
 */
tdl::TDLKeyCodes tdl::InputKeyboard::charToKeyCodes(char key)
{
    return static_cast<TDLKeyCodes>(key);
}