#include "GUI.hpp"
#include <iostream>

Button::Button(const std::string& label, const std::function<void()>& callback)
    : label(label), onClickCallback(callback) {}

void Button::render() {
    // Render the button (pseudo-code)
    std::cout << "Rendering button: " << label << std::endl;
}

void Button::onClick() {
    // Trigger the button's click callback
    if (onClickCallback) {
        onClickCallback();
    }
}