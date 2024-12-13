#ifndef INPUT_HPP
#define INPUT_HPP

#include <map>
#include <string>

class Input {
public:
    Input();
    ~Input();

    bool isKeyPressed(const std::string& key);
    bool isMousePressed(const std::string& button);
    void update();

private:
    std::map<std::string, bool> keyState;
    std::map<std::string, bool> mouseState;
};

#endif // INPUT_HPP