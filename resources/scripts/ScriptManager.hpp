// ScriptManager.hpp
#ifndef SCRIPTMANAGER_HPP
#define SCRIPTMANAGER_HPP

#include <string>

class ScriptManager {
public:
    static void loadScript(const std::string& filename);
    static void executeScript(const std::string& scriptName);
    static void unloadScript(const std::string& scriptName);
};

#endif // SCRIPTMANAGER_HPP