// PlatformFactory.hpp
#ifndef PLATFORMFACTORY_HPP
#define PLATFORMFACTORY_HPP

#include "Window.hpp"
#if defined(_WIN32)
    #include "windows/WindowWin.cpp"
#elif defined(__APPLE__)
    #include "macos/WindowMac.cpp"
#elif defined(__linux__)
    #include "linux/WindowLinux.cpp"
#endif

class PlatformFactory {
public:
    static Window* createWindow() {
#if defined(_WIN32)
        return new WindowWin();
#elif defined(__APPLE__)
        return new WindowMac();
#elif defined(__linux__)
        return new WindowLinux();
#else
        #error "Unsupported platform"
#endif
    }
};

#endif // PLATFORMFACTORY_HPP