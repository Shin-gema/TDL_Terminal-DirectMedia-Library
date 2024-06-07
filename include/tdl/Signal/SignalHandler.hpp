

#ifndef LIBNCURSE_SIGNALHANDLER_HPP
#define LIBNCURSE_SIGNALHANDLER_HPP

#include "tdl/Window.hpp"
#include <csignal>

namespace tdl {
/**
 * @class SignalHandler
 * @brief this class is in charge of handling all the signals for the windows
 * the pattern used is singleton
 */
    class SignalHandler {
        public:
/**
* @brief Construct or return the instance of the SignalHandler
*
* @return tdl::SignalHandler& the instance of the SignalHandler
*/
        static SignalHandler &getInstance();

        SignalHandler(SignalHandler const&) = delete;
        void operator=(SignalHandler const&) = delete;

/**
 * @brief register a new window to the signal handler
 * when you register an window you can be sure that the window will be updated when the terminal is resized
 *
 * @param win the window to register
 */
        void registerWindow(Window *win);

/**
 * @brief unregister a window from the signal handler
 *
 * @param win the window to unregister
 */
        void unRegisterWindow(Window *win);

/**
 * @brief the function called when a signal is received
 *
 * @param sig the signal received
 */
        static void handleSignal(int sig);

        private:
/**
 * @brief Construct a new Signal Handler object
 *
 */
        SignalHandler() {
            std::signal(SIGWINCH, SignalHandler::handleSignal);
        }

/**
 * @brief the instance off the signal recieve
 * this manage all the window registered to the signal handler
 *
 */
        void handleSignalInstance();

        std::vector<Window*> _windows; /**< the list of windows registered to the signal handler */
    };
}

#endif //LIBNCURSE_SIGNALHANDLER_HPP
