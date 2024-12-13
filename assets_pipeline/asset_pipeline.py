from texture_importer import TextureImporter
from texture_processor import TextureProcessor
from asset_exporter import AssetExporter

class AssetPipeline:
    def __init__(self):
        self.importer = TextureImporter('assets/raw/textures', 'assets/textures')
        self.processor = TextureProcessor('assets/textures')
        self.exporter = AssetExporter('assets/textures', 'assets/final/textures')

    def run(self):
        # Step 1: Import assets
        self.importer.import_texture('hero_texture.jpg')

        # Step 2: Process assets (compress)
        self.processor.compress_texture('hero_texture.jpg')

        # Step 3: Export assets
        self.exporter.export_asset('hero_texture.jpg')

pipeline = AssetPipeline()
pipeline.run()