
# pragma once

#include <iostream>
#include <queue>
#include "Event/Event.hpp"
#include "Input/inputKeyboard.hpp"

namespace tdl {
    class WindowBase : public InputKeyboard {
        public:
            WindowBase(std::string fdPath);
            ~WindowBase();
            bool pollEvent(Event &event);
            void pushEvent(const Event &event);
            int getFd() const { return _fd; }

        protected:
            
            std::queue<Event> _events;
            InputKeyboard _input;
            int _fd;
            std::string _fdPath;
    };
}