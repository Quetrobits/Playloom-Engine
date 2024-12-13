#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <json/json.h> // Include a JSON library to read the metadata

class AudioManager {
public:
    void loadAudio(const std::string& audioPath) {
        std::cout << "Loading audio from: " << audioPath << std::endl;
        // Actual audio loading logic (use FMOD or SDL_Mixer here)
    }

    void playAudio(const std::string& audioPath, bool loop = false, float volume = 1.0f) {
        std::cout << "Playing audio: " << audioPath << " | Loop: " << loop << " | Volume: " << volume << std::endl;
        // Implement audio playback logic here
    }

    void loadAudioMetadata(const std::string& metadataPath) {
        std::cout << "Loading audio metadata from: " << metadataPath << std::endl;

        // Parse the metadata JSON file
        Json::Value root;
        Json::Reader reader;
        std::ifstream file(metadataPath);
        reader.parse(file, root);

        for (const auto& audio : root["audio"]) {
            std::string audioName = audio["name"].asString();
            bool loop = audio["loop"].asBool();
            float volume = audio["volume"].asFloat();

            loadAudio("assets/audio/" + audioName);
            playAudio("assets/audio/" + audioName, loop, volume);
        }
    }
};

// Example usage
int main() {
    AudioManager audioManager;
    audioManager.loadAudioMetadata("assets/audio/metadata.json");
    
    return 0;
}