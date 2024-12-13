// ShaderLoader.hpp
#ifndef SHADERLOADER_HPP
#define SHADERLOADER_HPP

#include <string>

class ShaderLoader {
public:
    static bool loadShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
    static void unloadShader(const std::string& shaderName);
};

#endif // SHADERLOADER_HPP