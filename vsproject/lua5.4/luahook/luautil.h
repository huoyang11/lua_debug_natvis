#ifndef __LUAUTIL_H__
#define __LUAUTIL_H__

#include <string>

struct lua_State;
struct lua_Debug;
std::string get_function_name(struct lua_State *L, struct lua_Debug *ar);

#endif