#include <iostream>
#include <string>
#include <vector>

// A simple class for managing assets in Playloom Engine
class AssetManager {
public:
    void loadModel(const std::string& modelPath) {
        std::cout << "Loading model from: " << modelPath << std::endl;
        // Implement loading logic here
    }

    void loadTexture(const std::string& texturePath) {
        std::cout << "Loading texture from: " << texturePath << std::endl;
        // Implement loading logic here
    }

    void loadAudio(const std::string& audioPath) {
        std::cout << "Loading audio from: " << audioPath << std::endl;
        // Implement loading logic here
    }
};

// Example of usage
int main() {
    AssetManager assetManager;
    assetManager.loadModel("models/character.obj");
    assetManager.loadTexture("textures/grass.png");
    assetManager.loadAudio("audio/background.mp3");

    return 0;
}