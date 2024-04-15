/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** SignalHandler.cpp
*/

#include "Signal/SignalHandler.hpp"
#include "Event/Event.hpp"
#include <algorithm>

/**
 * @brief Construct or return the instance of the SignalHandler
 * 
 * @return tdl::SignalHandler& the instance of the SignalHandler
 */
tdl::SignalHandler &tdl::SignalHandler::getInstance()
{
    static SignalHandler instance;
    return instance;
}

/**
 * @brief register a new window to the signal handler
 * when you register an window you can be sure that the window will be updated when the terminal is resized
 * 
 * @param win the window to register
 */
void tdl::SignalHandler::registerWindow(Window *win)
{
    _windows.push_back(win);
}

/**
 * @brief unregister a window from the signal handler
 * 
 * @param win the window to unregister
 */
void tdl::SignalHandler::unRegisterWindow(Window *win)
{
    _windows.erase(std::remove(_windows.begin(), _windows.end(), win), _windows.end());
}

/**
 * @brief the function called when a signal is received
 *
 * @param sig the signal received
 */
void tdl::SignalHandler::handleSignal(int sig)
{
    if (sig == SIGWINCH)
        getInstance().handleSignalInstance();
}

/**
 * @brief the instance off the signal recieve
 * this manage a
 * 
 */
void tdl::SignalHandler::handleSignalInstance()
{
    for (auto &win : _windows) {
        win->updateTermSize();
        Event event;
        event.type = Event::EventType::WindowResized;
        event.size.width = win->getWidth();
        event.size.height = win->getHeight();
        win->pushEvent(event);
    }
}