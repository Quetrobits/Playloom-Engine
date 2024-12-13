#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <string>
#include <vector>
#include "Shader.hpp"
#include "Texture.hpp"
#include "Model.hpp"

class Graphics {
public:
    Graphics();
    ~Graphics();

    void initialize();
    void renderScene();
    void setClearColor(float r, float g, float b);
    void loadShader(const std::string& vertexPath, const std::string& fragmentPath);
    void loadTexture(const std::string& texturePath);
    void drawModel(const Model& model);

private:
    Shader currentShader;
    std::vector<Texture> textures;
};

#endif // GRAPHICS_HPP