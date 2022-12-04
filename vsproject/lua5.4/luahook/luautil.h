#ifndef __LUAUTIL_H__
#define __LUAUTIL_H__

#include <string>

struct lua_State;
struct lua_Debug;
std::string get_function_name(struct lua_State *L, struct lua_Debug *ar);

int lua_dofile(struct lua_State *L,const std::string &filepath);

int lua_require(struct lua_State* L, const std::string& filepath);

int lua_addcpath(struct lua_State* L, const std::string& cpath);

int lua_addpath(struct lua_State* L, const std::string& path);

std::string lua_getglobal(struct lua_State* L, const std::string& globalname);

std::string lua_dostring(struct lua_State* L, const std::string &code);


#endif