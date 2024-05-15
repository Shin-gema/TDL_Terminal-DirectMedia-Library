
#include <iostream> 
#include <queue>
#include "tdl/Event/Event.hpp"
#include "tdl/Window/windowBase.hpp"
#include "tdl/Input/inputKeyboard.hpp"

tdl::WindowBase::WindowBase( std::string fdPath)
    : _fdPath(fdPath)
{
    _input = InputKeyboard();
}

tdl::WindowBase::~WindowBase()
{
}

/**
 * @brief Polls the event
 * this function will return the event and pop it from the queue
 * before that it will check if any event flag is set
 * 
 * @param event the event to return
 * @return true if an event is found
 * @return false if no event is found
 */
bool tdl::WindowBase::pollEvent(tdl::Event &event)
{
    if (_events.empty()){
        _input.readInputKeyboard(this);
    }
    if (!_events.empty()){
        event = _events.front();
        _events.pop();
        return true;
    }
    return false;
}

/**
 * @brief push an event into the queue
 * that permited to register an event when you want to
 * 
 * @param event the event to push in the queue
 */
void tdl::WindowBase::pushEvent(const tdl::Event &event)
{
    _events.push(event);
}