/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** SignalHandler.hpp
*/

#ifndef LIBNCURSE_SIGNALHANDLER_HPP
#define LIBNCURSE_SIGNALHANDLER_HPP

#include "Window.hpp"
#include <csignal>

namespace tdl {
    /**
     * @brief this class is in charge of handling all the signals for the windows
     * the pattern used is singleton
     */
    class SignalHandler {
        public:
        static SignalHandler &getInstance();

        SignalHandler(SignalHandler const&) = delete;
        void operator=(SignalHandler const&) = delete;

        void registerWindow(Window *win);
        void unRegisterWindow(Window *win);

        static void handleSignal(int sig);

        private:
        SignalHandler() {
            std::signal(SIGWINCH, SignalHandler::handleSignal);
        }
        void handleSignalInstance();

        std::vector<Window*> _windows;
    };
}

#endif //LIBNCURSE_SIGNALHANDLER_HPP
