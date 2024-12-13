// ModelLoader.hpp
#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include <string>

class ModelLoader {
public:
    static bool loadModel(const std::string& filename);
    static void unloadModel(const std::string& modelName);
};

#endif // MODELLOADER_HPP