#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// A simple importer that could be expanded for specific file conversions
class ModelImporter {
public:
    void importModel(const std::string& modelPath) {
        std::cout << "Importing model from: " << modelPath << std::endl;

        // For now, just simulate the process (you would include actual importing logic here)
        if (fs::exists(modelPath)) {
            std::cout << "Model " << modelPath << " imported successfully." << std::endl;
        } else {
            std::cout << "Error: Model file does not exist at " << modelPath << std::endl;
        }
    }

    void batchImportModels(const std::string& directoryPath) {
        std::cout << "Batch importing models from: " << directoryPath << std::endl;
        
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.is_regular_file() && (entry.path().extension() == ".obj" || entry.path().extension() == ".fbx" || entry.path().extension() == ".gltf")) {
                importModel(entry.path().string());
            }
        }
    }
};

// Example usage
int main() {
    ModelImporter importer;
    importer.importModel("assets/models/character.obj");
    importer.batchImportModels("assets/models");
    
    return 0;
}