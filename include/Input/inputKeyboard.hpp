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
#include "EInput.hpp"
#include <map>

namespace tdl {

    class WindowBase;

    class InputKeyboard {
    public:
        InputKeyboard();
        ~InputKeyboard();

        void readInputKeyboard(WindowBase *window);
        TDLKeyCodes charToKeyCodes(char key);

    protected:
        TDLKeyCodes _shared_data;
        std::map<char, bool> _key_states;
        std::map<char, bool> _prev_key_states;
    };
} // namespace tdl

#endif //LIBNCURSE_INPUT_HPP
