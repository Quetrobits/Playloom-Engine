// GUI APPEARANCE WARNING  
// ------------------------------------------------------------  
// As this pertains to the core appearance of the GUI, you are permitted to  
// modify these elements. However, please be aware that altering  
// any of these components can lead to the GUI displaying incorrectly or  
// potentially becoming completely unusable. While changes  
// are possible, we strongly advise against modifying these files  
// to avoid compromising the user interface's functionality or aesthetics.  
// Any modifications made are at your own risk and could result in  
// severe visual glitches or performance issues!  
// ------------------------------------------------------------  

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <chrono>

// --- Helper Classes ---
sf::Texture loadTextureFromURL(const std::string &url) {
    sf::Texture texture;
    if (!texture.loadFromFile(url)) {
        std::cout << "Failed to load image from " << url << std::endl;
    }
    return texture;
}

// --- Button ---
class Button : public GUIElement {
private:
    sf::RectangleShape buttonShape;
    sf::Text buttonText;
    std::function<void()> onClick;

public:
    Button(const std::string &label, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Font &font)
    {
        buttonShape.setPosition(position);
        buttonShape.setSize(size);
        buttonShape.setFillColor(sf::Color::Green);

        buttonText.setString(label);
        buttonText.setFont(font);
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(position.x + (size.x - buttonText.getGlobalBounds().width) / 2,
                               position.y + (size.y - buttonText.getGlobalBounds().height) / 2);
    }

    void setOnClick(std::function<void()> func) {
        onClick = func;
    }

    void draw(sf::RenderWindow &window) override {
        window.draw(buttonShape);
        window.draw(buttonText);
    }

    void handleEvent(const sf::Event &event) override {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOver(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) {
                if (onClick) {
                    onClick();
                }
            }
        }
    }

    bool isMouseOver(const sf::Vector2i &mousePosition) override {
        sf::FloatRect bounds = buttonShape.getGlobalBounds();
        return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }
};

// --- Slider ---
class Slider : public GUIElement {
private:
    sf::RectangleShape sliderTrack;
    sf::RectangleShape sliderThumb;
    float minValue, maxValue, currentValue;

public:
    Slider(const sf::Vector2f &position, float minVal, float maxVal, float initialValue, const sf::Vector2f &size)
        : minValue(minVal), maxValue(maxVal), currentValue(initialValue) {
        sliderTrack.setPosition(position);
        sliderTrack.setSize(size);
        sliderTrack.setFillColor(sf::Color(200, 200, 200));

        sliderThumb.setSize(sf::Vector2f(20, size.y));
        sliderThumb.setFillColor(sf::Color::Blue);
        updateThumbPosition();
    }

    void updateThumbPosition() {
        float normalizedValue = (currentValue - minValue) / (maxValue - minValue);
        sliderThumb.setPosition(sliderTrack.getPosition().x + normalizedValue * (sliderTrack.getSize().x - sliderThumb.getSize().x),
                               sliderTrack.getPosition().y);
    }

    void draw(sf::RenderWindow &window) override {
        window.draw(sliderTrack);
        window.draw(sliderThumb);
    }

    void handleEvent(const sf::Event &event) override {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOver(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))) {
                currentValue = minValue + (event.mouseButton.x - sliderTrack.getPosition().x) / sliderTrack.getSize().x * (maxValue - minValue);
                updateThumbPosition();
            }
        }
    }

    bool isMouseOver(const sf::Vector2i &mousePosition) override {
        sf::FloatRect bounds = sliderThumb.getGlobalBounds();
        return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }

    float getValue() const {
        return currentValue;
    }

    void setValue(float value) {
        currentValue = value;
        updateThumbPosition();
    }
};

// --- Scene Handler ---
class Scene {
private:
    std::string name;
    std::vector<GUIElement*> elements;

public:
    Scene(const std::string &sceneName) : name(sceneName) {}

    void addElement(GUIElement* element) {
        elements.push_back(element);
    }

    void draw(sf::RenderWindow &window) {
        for (auto* element : elements) {
            element->draw(window);
        }
    }

    void handleEvent(const sf::Event &event) {
        for (auto* element : elements) {
            element->handleEvent(event);
        }
    }

    const std::string& getName() const {
        return name;
    }
};

// --- Viewbox ---
class Viewbox : public GUIElement {
private:
    sf::RectangleShape boxShape;
    sf::View view;

public:
    Viewbox(const sf::Vector2f &position, const sf::Vector2f &size) {
        boxShape.setPosition(position);
        boxShape.setSize(size);
        boxShape.setFillColor(sf::Color(220, 220, 220));
    }

    void setView(const sf::View &newView) {
        view = newView;
    }

    void draw(sf::RenderWindow &window) override {
        window.setView(view);
        window.draw(boxShape);
    }

    void handleEvent(const sf::Event &event) override {
        // Handle scroll events here
    }

    bool isMouseOver(const sf::Vector2i &mousePosition) override {
        sf::FloatRect bounds = boxShape.getGlobalBounds();
        return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }
};

// --- Scripting (Lua and C Editor) ---
class ScriptEditor : public GUIElement {
private:
    sf::RectangleShape editorBox;
    sf::Text editorText;
    sf::Font font;
    std::string codeContent;
    bool isLuaMode;

public:
    ScriptEditor(const sf::Vector2f &position, const sf::Font &font) : isLuaMode(true) {
        editorBox.setPosition(position);
        editorBox.setSize(sf::Vector2f(600, 400));
        editorBox.setFillColor(sf::Color(50, 50, 50, 150));

        editorText.setFont(font);
        editorText.setCharacterSize(20);
        editorText.setFillColor(sf::Color::White);
        editorText.setPosition(position.x + 10, position.y + 10);
    }

    void setCodeContent(const std::string &content) {
        codeContent = content;
        editorText.setString(content);
    }

    void toggleLanguage() {
        isLuaMode = !isLuaMode;
    }

    void draw(sf::RenderWindow &window) override {
        window.draw(editorBox);
        window.draw(editorText);
    }

    void handleEvent(const sf::Event &event) override {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                codeContent += static_cast<char>(event.text.unicode);
            }
        }
        editorText.setString(codeContent);
    }

    bool isMouseOver(const sf::Vector2i &mousePosition) override {
        sf::FloatRect bounds = editorBox.getGlobalBounds();
        return bounds.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }

    std::string getCode() const {
        return codeContent;
    }
};

// --- Language Selector ---
class LanguageSelector : public GUIElement {
private:
    Button luaButton;
    Button cButton;
    std::function<void(const std::string&)> onLanguageChange;

public:
    LanguageSelector(const sf::Vector2f &position, const sf::Font &font) 
        : luaButton("Lua", position, sf::Vector2f(100, 50), font), cButton("C", sf::Vector2f(position.x + 110, position.y), sf::Vector2f(100, 50), font) {
        
        luaButton.setOnClick([this]() {
            if (onLanguageChange) onLanguageChange("Lua");
        });

        cButton.setOnClick([this]() {
            if (onLanguageChange) onLanguageChange("C");
        });
    }

    void setOnLanguageChange(std::function<void(const std::string&)> func) {
        onLanguageChange = func;
    }

    void draw(sf::RenderWindow &window) override {
        luaButton.draw(window);
        cButton.draw(window);
    }

    void handleEvent(const sf::Event &event) override {
        luaButton.handleEvent(event);
        cButton.handleEvent(event);
    }

    bool isMouseOver(const sf::Vector2i &mousePosition) override {
        return luaButton.isMouseOver(mousePosition) || cButton.isMouseOver(mousePosition);
    }
};

// --- Logo Display ---
class LogoDisplay : public GUIElement {
private:
    sf::Sprite logo;
    sf::Texture logoTexture;

public:
    LogoDisplay(const std::string &imagePath, const sf::Vector2f &position) {
        logoTexture = loadTextureFromURL(imagePath);
        logo.setTexture(logoTexture);
        logo.setPosition(position);
    }

    void draw(sf::RenderWindow &window) override {
        window.draw(logo);
    }

    void handleEvent(const sf::Event &event) override {
        // Handle any event related to the logo (if interactive)
    }

    bool isMouseOver(const sf::Vector2i &mousePosition) override {
        return logo.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
    }
};

// --- Main Application ---
class Application {
private:
    sf::RenderWindow window;
    sf::Font font;
    Scene *currentScene;
    Scene *mainMenuScene;
    Scene *scriptScene;
    LanguageSelector languageSelector;
    ScriptEditor scriptEditor;
    Animator animator;
    LogoDisplay logoDisplay;

public:
    Application() : window(sf::VideoMode(800, 600), "Advanced Game Engine"), languageSelector(sf::Vector2f(10, 10), font), scriptEditor(sf::Vector2f(10, 70), font), logoDisplay("http://playloom.com/logo.png", sf::Vector2f(300, 10)) {
        if (!font.loadFromFile("arial.ttf")) {
            std::cerr << "Error loading font!" << std::endl;
        }

        // Create scenes
        mainMenuScene = new Scene("Main Menu");
        scriptScene = new Scene("Script Editor");

        // Add GUI elements
        mainMenuScene->addElement(&languageSelector);
        mainMenuScene->addElement(&logoDisplay);
        scriptScene->addElement(&scriptEditor);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                currentScene->handleEvent(event);
            }

            window.clear();
            currentScene->draw(window);
            window.display();
        }
    }

    void switchScene(Scene *newScene) {
        currentScene = newScene;
    }
};

// --- Main Entry ---
int main() {
    Application app;
    app.run();
    return 0;
}