#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <type_traits>
#include <cassert>

class SceneObject {
public:
    virtual ~SceneObject() = default;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual std::string GetName() const = 0;
};

class Scene {
public:
    Scene(const std::string& name) : name(name) {}

    void AddObject(const std::shared_ptr<SceneObject>& object) {
        objects[object->GetName()] = object;
    }

    void RemoveObject(const std::string& name) {
        objects.erase(name);
    }

    std::shared_ptr<SceneObject> GetObject(const std::string& name) const {
        auto it = objects.find(name);
        return it != objects.end() ? it->second : nullptr;
    }

    void Update(float deltaTime) {
        for (auto& [name, object] : objects) {
            object->Update(deltaTime);
        }
    }

    void Render() {
        for (auto& [name, object] : objects) {
            object->Render();
        }
    }

    std::string GetName() const { return name; }

private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<SceneObject>> objects;
};

class SceneManager {
public:
    SceneManager() = default;

    void CreateScene(const std::string& name) {
        assert(scenes.find(name) == scenes.end() && "Scene already exists!");
        scenes[name] = std::make_shared<Scene>(name);
    }

    void RemoveScene(const std::string& name) {
        if (activeScene && activeScene->GetName() == name) {
            activeScene.reset();
        }
        scenes.erase(name);
    }

    void SetActiveScene(const std::string& name) {
        auto it = scenes.find(name);
        assert(it != scenes.end() && "Scene does not exist!");
        activeScene = it->second;
    }

    std::shared_ptr<Scene> GetActiveScene() const { return activeScene; }

    void Update(float deltaTime) {
        if (activeScene) {
            activeScene->Update(deltaTime);
        }
    }

    void Render() {
        if (activeScene) {
            activeScene->Render();
        }
    }

private:
    std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
    std::shared_ptr<Scene> activeScene;
};

// Example of a custom SceneObject
class Cube : public SceneObject {
public:
    Cube(const std::string& name) : name(name) {}

    void Update(float deltaTime) override {
        // Example logic: Rotate the cube
        rotation += deltaTime * 50.0f; // degrees per second
        if (rotation >= 360.0f) rotation -= 360.0f;
    }

    void Render() override {
        std::cout << "Rendering Cube: " << name << " at rotation " << rotation << "\n";
    }

    std::string GetName() const override { return name; }

private:
    std::string name;
    float rotation = 0.0f;
};

int main() {
    SceneManager sceneManager;

    // Create scenes
    sceneManager.CreateScene("MainMenu");
    sceneManager.CreateScene("GameLevel");

    // Add objects to scenes
    auto cube = std::make_shared<Cube>("Cube1");
    sceneManager.GetActiveScene()->AddObject(cube);

    sceneManager.SetActiveScene("GameLevel");
    sceneManager.GetActiveScene()->AddObject(cube);

    // Game loop
    const float deltaTime = 0.016f; // Assuming 60 FPS
    for (int i = 0; i < 5; ++i) {
        sceneManager.Update(deltaTime);
        sceneManager.Render();
    }

    return 0;
}