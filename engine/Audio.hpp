#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <string>
#include <map>

class Audio {
public:
    Audio();
    ~Audio();

    void initialize();
    void playSound(const std::string& soundPath);
    void stopSound(const std::string& soundPath);
    void setVolume(float volume);

private:
    std::map<std::string, std::string> sounds;
    float volume;
};

#endif // AUDIO_HPP