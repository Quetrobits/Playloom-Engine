// texture_importer.cpp
#include <iostream>
#include <string>
#include "TextureLoader.hpp"

void importTexture(const std::string& filePath) {
    if (TextureLoader::loadTexture(filePath)) {
        std::cout << "Texture imported successfully: " << filePath << std::endl;
    } else {
        std::cerr << "Failed to import texture: " << filePath << std::endl;
    }
}