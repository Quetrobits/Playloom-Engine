// AudioManager.hpp
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <string>
#include <map>

class AudioManager {
public:
    AudioManager();
    ~AudioManager();

    void playSound(const std::string& soundFile);
    void stopSound(const std::string& soundFile);

private:
    std::map<std::string, Sound*> sounds;
};

#endif // AUDIOMANAGER_HPP