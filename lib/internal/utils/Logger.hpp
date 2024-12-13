// Logger.hpp
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>

class Logger {
public:
    static void log(const std::string& message) {
        std::cout << "[LOG]: " << message << std::endl;
    }

    static void error(const std::string& message) {
        std::cerr << "[ERROR]: " << message << std::endl;
    }
};

#endif // LOGGER_HPP