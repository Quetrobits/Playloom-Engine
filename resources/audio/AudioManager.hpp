// AudioManager.hpp
#ifndef AUDIOMANAGER_HPP
#define AUDIOMANAGER_HPP

#include <string>

class AudioManager {
public:
    static void loadSound(const std::string& filename);
    static void playSound(const std::string& soundName);
    static void stopSound(const std::string& soundName);
    static void unloadSound(const std::string& soundName);
};

#endif // AUDIOMANAGER_HPP