#ifndef CONFIGLOADER_HPP
#define CONFIGLOADER_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

class ConfigLoader {
public:
    // Constructor that loads a config file from the provided path
    ConfigLoader(const std::string& filePath);

    // Method to get a value from the config file using a key
    template <typename T>
    T get(const std::string& key);

    // Method to check if a key exists in the configuration file
    bool contains(const std::string& key) const;

private:
    nlohmann::json configData;  // Holds the loaded JSON data

    // Method to load the JSON data from the config file
    void loadConfig(const std::string& filePath);
};

#endif // CONFIGLOADER_HPP