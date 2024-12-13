// ResourceManager.hpp
#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include "Texture.hpp"

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    Texture* loadTexture(const std::string& filename);
    void unloadTexture(const std::string& filename);

private:
    std::map<std::string, Texture*> textures;
};

#endif // RESOURCEMANAGER_HPP