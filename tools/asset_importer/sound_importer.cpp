#include "sound_importer.h"
#include <iostream>
#include <map>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include "audio_loader.h"

class SoundImporter {
public:
    SoundImporter(const std::string& path) {
        loadSound(path);
    }

    void play() {
        if (buffer != 0) {
            alGenSources(1, &source);
            alSourcei(source, AL_BUFFER, buffer);
            alSourcePlay(source);
        }
    }

    void stop() {
        if (source != 0) {
            alSourceStop(source);
        }
    }

    ~SoundImporter() {
        if (source != 0) {
            alDeleteSources(1, &source);
        }
        if (buffer != 0) {
            alDeleteBuffers(1, &buffer);
        }
    }

private:
    ALuint buffer = 0;
    ALuint source = 0;

    void loadSound(const std::string& path) {
        ALenum format;
        ALsizei freq;
        std::vector<char> audioData;

        if (!AudioLoader::loadAudioFromFile(path, format, freq, audioData)) {
            std::cerr << "ERROR::SOUND_IMPORTER::Failed to load sound from file: " << path << std::endl;
            return;
        }

        alGenBuffers(1, &buffer);
        alBufferData(buffer, format, audioData.data(), static_cast<ALsizei>(audioData.size()), freq);

        ALenum error = alGetError();
        if (error != AL_NO_ERROR) {
            std::cerr << "ERROR::SOUND_IMPORTER::OpenAL error: " << alGetString(error) << std::endl;
            if (buffer != 0) {
                alDeleteBuffers(1, &buffer);
                buffer = 0;
            }
        }
    }
};