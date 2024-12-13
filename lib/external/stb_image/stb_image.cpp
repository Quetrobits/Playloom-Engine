#include "stb_image/stb_image.h"

int width, height, channels;
unsigned char* data = stbi_load("texture.png", &width, &height, &channels, 0);
if (!data) {
    std::cerr << "Failed to load image." << std::endl;
}