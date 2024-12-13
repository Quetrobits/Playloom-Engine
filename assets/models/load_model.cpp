#include <iostream>
#include <string>

// Simple Asset Loader for models
class ModelLoader {
public:
    void loadModel(const std::string& modelPath) {
        std::cout << "Loading model from: " << modelPath << std::endl;
        
        // Add your code here to load the actual model data (e.g., .obj, .fbx, .gltf)
        // Example: using an external library to load model data
    }

    void listModelsInFolder(const std::string& folderPath) {
        // This would list all model files in the specified folder
        // Example: `models/` folder might contain .obj, .fbx, etc.
        std::cout << "Listing models in folder: " << folderPath << std::endl;
        // You could use filesystem APIs or third-party libraries to list files here
    }
};

// Example usage
int main() {
    ModelLoader loader;
    loader.loadModel("assets/models/character.obj");
    loader.listModelsInFolder("assets/models");
    
    return 0;
}