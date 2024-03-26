/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** input.hpp
*/

#ifndef LIBNCURSE_INPUT_HPP
    #define LIBNCURSE_INPUT_HPP

#include <thread>
#include <mutex>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include "../logger/logger.hpp"
#include "../window/window.hpp"
#include "EInput.hpp"
#include <map>

class Input {
public:
    Input();
    ~Input();

    void disableEcho();
    char getKeyCode();
    bool on_pressed(char key);
    bool on_maintain(char key);
    bool on_release(char key);
    void readInput(Window *win);

private:

    char _shared_data;
    std::map<char, bool> _key_states;
    std::map<char, bool> _prev_key_states;
};

#endif //LIBNCURSE_INPUT_HPP
