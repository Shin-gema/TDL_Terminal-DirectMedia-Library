//
// Created by thomas on 24/03/24.
//

#include "logger.hpp"
#include <chrono>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>

Logger* Logger::instance = nullptr;

Logger::Logger(const std::string& filename) {
    if (!filename.empty()) {
        _file.open(filename, std::ios::out | std::ios::trunc);
        if (!_file.is_open()) {
            std::cerr << "Error: could not open file " << filename << std::endl;
            exit(84);
        }
        _filename = filename;
    }
}
Logger* Logger::getInstance(const std::string& filename) {
    if (instance == nullptr) {
        instance = new Logger(filename);
    }
    return instance;
}

Logger::~Logger()
{
    _file.close();
}

void Logger::log(const std::string& message, const std::string& function_name = __PRETTY_FUNCTION__) {
    if (!print_log)
        return;
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));

    std::string formatted_message = "[" + std::string(date) + "][" + function_name + "]: " + message;

    _file << formatted_message << std::endl;
}