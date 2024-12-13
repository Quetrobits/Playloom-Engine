#ifndef ENGINECORE_HPP
#define ENGINECORE_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include "Graphics.hpp"
#include "Input.hpp"
#include "Audio.hpp"
#include "Physics.hpp"
#include "GUI.hpp"
#include "AssetManager.hpp"
#include "SceneManager.hpp"

class EngineCore {
public:
    EngineCore();
    ~EngineCore();

    // Main engine loop
    void run();

    // Initialize all subsystems
    void initialize();

    // Update the engine systems
    void update(float deltaTime);

    // Render the game
    void render();

private:
    std::shared_ptr<Graphics> graphics;
    std::shared_ptr<Input> input;
    std::shared_ptr<Audio> audio;
    std::shared_ptr<Physics> physics;
    std::shared_ptr<GUI> gui;
    std::shared_ptr<AssetManager> assetManager;
    std::shared_ptr<SceneManager> sceneManager;
};

#endif // ENGINECORE_HPP