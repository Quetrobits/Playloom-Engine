#include "lua/lua.hpp"

lua_State* L = luaL_newstate();
luaL_openlibs(L);

// Run a Lua script
if (luaL_dofile(L, "script.lua") != LUA_OK) {
    std::cerr << "Failed to run Lua script." << std::endl;
}
lua_close(L);