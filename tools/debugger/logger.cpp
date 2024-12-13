// logger.cpp
#include <iostream>

void logError(const std::string& message) {
    std::cerr << "ERROR: " << message << std::endl;
}

void logInfo(const std::string& message) {
    std::cout << "INFO: " << message << std::endl;
}