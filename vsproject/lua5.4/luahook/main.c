#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <lstate.h>
#include <ldebug.h>
#include <lopcodes.h>
#include <lopnames.h>

int count = 0;

#define COMMENT		"\t; "
#define EXTRAARG	GETARG_Ax(code[pc+1])
#define EXTRAARGC	(EXTRAARG*(MAXARG_C+1))
#define ISK		(isk ? "k" : "")

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