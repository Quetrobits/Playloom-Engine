import os

class AudioManager:
    def load_audio(self, audio_path):
        print(f"Loading audio from: {audio_path}")
        # Add your audio loading logic here (e.g., using pygame, pydub, or other libraries)

    def play_audio(self, audio_path):
        print(f"Playing audio: {audio_path}")
        # Implement audio playback (e.g., using pygame.mixer or another audio library)

    def batch_import_audio(self, directory_path):
        print(f"Batch importing audio from: {directory_path}")
        for filename in os.listdir(directory_path):
            if filename.endswith((".mp3", ".wav", ".ogg")):
                self.load_audio(os.path.join(directory_path, filename))

# Example usage
if __name__ == "__main__":
    audio_manager = AudioManager()
    audio_manager.load_audio("assets/audio/music/background_music.mp3")
    audio_manager.play_audio("assets/audio/sfx/explosion.wav")
    audio_manager.batch_import_audio("assets/audio")