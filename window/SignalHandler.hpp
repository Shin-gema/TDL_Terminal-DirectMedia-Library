/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** SignalHandler.hpp
*/

#ifndef LIBNCURSE_SIGNALHANDLER_HPP
#define LIBNCURSE_SIGNALHANDLER_HPP

#include "window.hpp"
#include <csignal>

class SignalHandler {
    public:
    static SignalHandler &getInstance();

    SignalHandler(SignalHandler const&) = delete;
    void operator=(SignalHandler const&) = delete;

    void registerWindow(Window *win);
    void unregisterWindow(Window *win);

    static void handleSignal(int sig);

    private:
    SignalHandler() {
        std::signal(SIGWINCH, SignalHandler::handleSignal);
    }
    void handleSignalInstance(int sig);

    std::vector<Window*> windows;
};

#endif //LIBNCURSE_SIGNALHANDLER_HPP
