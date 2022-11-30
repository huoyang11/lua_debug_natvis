#include "luacommon.h"
#include "luautil.h"
#include <string.h>

int count = 0;

//void funcinfo(lua_Debug* ar, Closure* cl) {
//    if (noLuaClosure(cl)) {
//        ar->source = "=[C]";
//        ar->srclen = LL("=[C]");
//        ar->linedefined = -1;
//        ar->lastlinedefined = -1;
//        ar->what = "C";
//    }
//    else {
//        const Proto* p = cl->l.p;
//        if (p->source) {
//            ar->source = getstr(p->source);
//            ar->srclen = tsslen(p->source);
//        }
//        else {
//            ar->source = "=?";
//            ar->srclen = LL("=?");
//        }
//        ar->linedefined = p->linedefined;
//        ar->lastlinedefined = p->lastlinedefined;
//        ar->what = (ar->linedefined == 0) ? "main" : "Lua";
//    }
//    luaO_chunkid(ar->short_src, ar->source, ar->srclen);
//}

void print_code(Instruction i)
{
	OpCode o = GET_OPCODE(i);
	printf("%-9s\n", opnames[o]);
}

void lua_Hook_call(lua_State* L, lua_Debug* ar)
{
    if (ar->event == LUA_HOOKCALL)
    {
        printf("event : hook call!\n");
        CallInfo* ci = ar->i_ci;
        if (!isLfunction(s2v((ci)->func))) return;
        const Proto* p = ci_func(ci)->p;
        lua_getinfo(L, "Slnt", ar);
        std::string funname = get_function_name(L,ar);
        //pushfuncname(L, ar);
        int a = 20;
    }

    if (ar->event == LUA_HOOKCOUNT)
    {
        printf("event : hook count!\n");
    }

    if (ar->event == LUA_HOOKRET)
    {
        printf("event : hook return!\n");
    }
    
    printf("count : %d\n", count++);

    CallInfo* ci = ar->i_ci;
    if (!isLfunction(s2v((ci)->func))) return;
    const Proto* p = ci_func(ci)->p;

    Instruction i = *(ci->u.l.savedpc);
    if (GET_OPCODE(i) < sizeof(opnames) / sizeof(opnames[0]))
        print_code(i);
    printf("\n");
}

int main(int argc, char* argv[])
{
    lua_State* L = luaL_newstate();

    luaL_openlibs(L);

    lua_sethook(L, lua_Hook_call, LUA_MASKCALL | LUA_MASKCOUNT | LUA_MASKRET,1);

    if (luaL_loadfile(L, "../test.lua") || lua_pcall(L, 0, 0, 0))
    {
        fprintf(stderr, "%s\n", lua_tostring(L, -1));
        lua_pop(L, 1);
        return -1;
    }

    lua_close(L);

    return 0;
}