import os
from PIL import Image

class TextureProcessor:
    def __init__(self, texture_folder):
        self.texture_folder = texture_folder

    def compress_texture(self, texture_filename):
        texture_path = os.path.join(self.texture_folder, texture_filename)
        if not os.path.exists(texture_path):
            print(f"Error: Texture {texture_filename} not found.")
            return

        img = Image.open(texture_path)

        # Compress texture (using lower quality)
        img.save(texture_path, quality=85, optimize=True)
        print(f"Texture compressed: {texture_filename}")

processor = TextureProcessor('assets/textures')
processor.compress_texture('hero_texture.jpg')