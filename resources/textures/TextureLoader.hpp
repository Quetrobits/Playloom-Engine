// TextureLoader.hpp
#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

#include <string>
#include <GL/glew.h>

class TextureLoader {
public:
    static GLuint loadTexture(const std::string& filename);
    static void unloadTexture(GLuint textureID);
};

#endif // TEXTURELOADER_HPP