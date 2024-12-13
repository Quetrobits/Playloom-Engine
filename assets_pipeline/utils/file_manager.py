import os

class FileManager:
    @staticmethod
    def create_directory(directory_path):
        if not os.path.exists(directory_path):
            os.makedirs(directory_path)
            print(f"Directory created: {directory_path}")
        else:
            print(f"Directory already exists: {directory_path}")

    @staticmethod
    def clean_directory(directory_path):
        if os.path.exists(directory_path):
            for file in os.listdir(directory_path):
                file_path = os.path.join(directory_path, file)
                if os.path.isfile(file_path):
                    os.remove(file_path)
                    print(f"Removed file: {file_path}")
            print(f"Directory cleaned: {directory_path}")
        else:
            print(f"Directory not found: {directory_path}")

file_manager = FileManager()
file_manager.create_directory('assets/textures')
file_manager.clean_directory('assets/raw/textures')