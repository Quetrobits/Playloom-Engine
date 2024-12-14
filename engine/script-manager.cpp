#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include <lua.hpp>

class ScriptManager {
public:
    ScriptManager(bool useLua = true) : useLuaEngine(useLua) {
        if (useLuaEngine) {
            luaState = luaL_newstate();
            luaL_openlibs(luaState);
        }
    }

    ~ScriptManager() {
        if (useLuaEngine) {
            lua_close(luaState);
        }
    }

    void LoadScript(const std::string& scriptName, const std::string& scriptContent) {
        if (useLuaEngine) {
            if (luaL_dostring(luaState, scriptContent.c_str()) != LUA_OK) {
                std::cerr << "Error loading Lua script " << scriptName << ": " << lua_tostring(luaState, -1) << "\n";
            } else {
                scripts[scriptName] = scriptContent;
            }
        } else {
            // Placeholder for C-based script management
            std::cerr << "C-based scripting not implemented yet." << std::endl;
        }
    }

    void RunFunction(const std::string& scriptName, const std::string& functionName, const std::vector<std::string>& args) {
        if (useLuaEngine) {
            if (scripts.find(scriptName) != scripts.end()) {
                lua_getglobal(luaState, functionName.c_str());
                for (const auto& arg : args) {
                    lua_pushstring(luaState, arg.c_str());
                }

                if (lua_pcall(luaState, args.size(), 0, 0) != LUA_OK) {
                    std::cerr << "Error executing function " << functionName << ": " << lua_tostring(luaState, -1) << "\n";
                }
            } else {
                std::cerr << "Script " << scriptName << " not loaded." << std::endl;
            }
        } else {
            std::cerr << "C-based function execution not implemented yet." << std::endl;
        }
    }

    void RegisterCustomFunction(const std::string& functionName, lua_CFunction function) {
        if (useLuaEngine) {
            lua_register(luaState, functionName.c_str(), function);
        } else {
            std::cerr << "Custom function registration for C-based scripts not implemented yet." << std::endl;
        }
    }

    void UnloadScript(const std::string& scriptName) {
        if (scripts.find(scriptName) != scripts.end()) {
            scripts.erase(scriptName);
        } else {
            std::cerr << "Script " << scriptName << " not found." << std::endl;
        }
    }

private:
    lua_State* luaState = nullptr;
    bool useLuaEngine;
    std::unordered_map<std::string, std::string> scripts;
};

// Example custom function for Lua integration
int PrintMessage(lua_State* L) {
    int args = lua_gettop(L);
    for (int i = 1; i <= args; ++i) {
        if (lua_isstring(L, i)) {
            std::cout << lua_tostring(L, i) << " ";
        } else {
            std::cerr << "Invalid argument type for PrintMessage function." << std::endl;
        }
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    ScriptManager manager(true);

    // Register a custom function
    manager.RegisterCustomFunction("PrintMessage", PrintMessage);

    // Load and execute a Lua script
    std::string script = R"(
        function greet(name)
            PrintMessage("Hello, " .. name .. "!")
        end
    )";

    manager.LoadScript("greeting", script);

    // Run the Lua function
    manager.RunFunction("greeting", "greet", {"World"});

    return 0;
}