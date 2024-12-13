// Window.hpp (common)
#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
public:
    virtual bool create(const char* title, int width, int height) = 0;
    virtual void destroy() = 0;
    virtual void update() = 0;
};

#endif // WINDOW_HPP