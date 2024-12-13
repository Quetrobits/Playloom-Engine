#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <string>

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void loadScene(const std::string& sceneName);
    void unloadScene(const std::string& sceneName);
    void updateScene(float deltaTime);
};

#endif // SCENEMANAGER_HPP