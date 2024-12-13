import os

class ModelImporter:
    def import_model(self, model_path):
        print(f"Importing model from: {model_path}")
        # Implement model importing logic here (use a library like pyassimp for model loading)
        # For example, converting .obj or .fbx to a game-specific format

    def batch_import_models(self, directory_path):
        print(f"Batch importing models from: {directory_path}")
        for filename in os.listdir(directory_path):
            if filename.endswith((".obj", ".fbx", ".gltf")):
                self.import_model(os.path.join(directory_path, filename))

# Example usage
if __name__ == "__main__":
    importer = ModelImporter()
    importer.import_model("assets/models/character.obj")
    importer.batch_import_models("assets/models")