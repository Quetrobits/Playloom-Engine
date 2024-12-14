#include "texture_importer.h"
#include <iostream>
#include <stb_image.h>
#include <GL/glew.h>

class TextureImporter {
public:
    TextureImporter(const std::string& path) {
        loadTexture(path);
    }

    void bind(unsigned int unit = 0) const {
        if (textureID != 0) {
            glActiveTexture(GL_TEXTURE0 + unit);
            glBindTexture(GL_TEXTURE_2D, textureID);
        }
    }

    ~TextureImporter() {
        if (textureID != 0) {
            glDeleteTextures(1, &textureID);
        }
    }

private:
    GLuint textureID = 0;

    void loadTexture(const std::string& path) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

        if (!data) {
            std::cerr << "ERROR::TEXTURE_IMPORTER::Failed to load texture: " << path << std::endl;
            return;
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLenum format = channels == 4 ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }
};