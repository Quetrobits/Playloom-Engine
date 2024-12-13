import os
import shutil

class AssetExporter:
    def __init__(self, source_folder, destination_folder):
        self.source_folder = source_folder
        self.destination_folder = destination_folder

    def export_asset(self, asset_filename):
        source_path = os.path.join(self.source_folder, asset_filename)
        if not os.path.exists(source_path):
            print(f"Error: Asset {asset_filename} not found.")
            return

        destination_path = os.path.join(self.destination_folder, asset_filename)
        shutil.copy(source_path, destination_path)
        print(f"Asset exported: {asset_filename}")

exporter = AssetExporter('assets/textures', 'assets/final/textures')
exporter.export_asset('hero_texture.jpg')