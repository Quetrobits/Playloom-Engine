import os
import shutil
from PIL import Image

class TextureImporter:
    def __init__(self, input_folder, output_folder):
        self.input_folder = input_folder
        self.output_folder = output_folder

    def import_texture(self, texture_filename):
        # Load the image
        input_path = os.path.join(self.input_folder, texture_filename)
        if not os.path.exists(input_path):
            print(f"Error: Texture {texture_filename} does not exist.")
            return

        img = Image.open(input_path)

        # Optionally, perform processing (e.g., resizing)
        img = img.resize((512, 512))

        # Save the processed texture to the output folder
        output_path = os.path.join(self.output_folder, texture_filename)
        img.save(output_path)
        print(f"Texture imported and saved to {output_path}")

importer = TextureImporter('assets/raw/textures', 'assets/textures')
importer.import_texture('hero_texture.jpg')