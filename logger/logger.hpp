/*
** EPITECH PROJECT, 2024
** libncurse
** File description:
** logger.hpp
*/

#ifndef LIBNCURSE_LOGGER_HPP
    #define LIBNCURSE_LOGGER_HPP


#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class Logger {
private:
    std::string _filename;
    u_int32_t _max_size = 10000;
    std::ofstream _file;
    bool print_log = true;
    static Logger* instance;
    Logger(const std::string& filename = "log.txt");

public:
    static Logger* getInstance(const std::string& filename = "log.txt");
    ~Logger();
    void log(const std::string& message, const std::string& function_name);
    void setPrintLog(bool print) { print_log = print; }
};

#define LOG(message) Logger::getInstance()->log(message, __PRETTY_FUNCTION__)

#endif //LIBNCURSE_LOGGER_HPP
