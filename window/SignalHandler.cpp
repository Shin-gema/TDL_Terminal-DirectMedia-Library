/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** SignalHandler.cpp
*/

#include "SignalHandler.hpp"
#include <algorithm>

SignalHandler &SignalHandler::getInstance()
{
    static SignalHandler instance;
    return instance;
}

void SignalHandler::registerWindow(Window *win)
{
    windows.push_back(win);
}

void SignalHandler::unregisterWindow(Window *win)
{
    windows.erase(std::remove(windows.begin(), windows.end(), win), windows.end());
}

void SignalHandler::handleSignal(int sig)
{
    getInstance().handleSignalInstance(sig);
}

void SignalHandler::handleSignalInstance(int sig)
{
    for (auto &win : windows) {
        win->updateTermSize();
    }
}