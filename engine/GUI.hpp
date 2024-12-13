#ifndef GUI_HPP
#define GUI_HPP

#include <string>
#include <vector>
#include <functional>

class Button {
public:
    Button(const std::string& label, const std::function<void()>& callback);
    void render();
    void onClick();

private:
    std::string label;
    std::function<void()> onClickCallback;
};

class GUI {
public:
    GUI();
    ~GUI();

    void initialize();
    void addButton(const std::string& label, const std::function<void()>& callback);
    void render();
    void update(float deltaTime);

private:
    std::vector<Button> buttons;
};

#endif // GUI_HPP