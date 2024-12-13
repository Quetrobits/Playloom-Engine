#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <string>
#include <map>
#include "Texture.hpp"
#include "Model.hpp"

class AssetManager {
public:
    AssetManager();
    ~AssetManager();

    Texture* loadTexture(const std::string& path);
    Model* loadModel(const std::string& path);
    void unloadTexture(const std::string& path);
    void unloadModel(const std::string& path);

private:
    std::map<std::string, Texture> textures;
    std::map<std::string, Model> models;
};

#endif // ASSETMANAGER_HPP