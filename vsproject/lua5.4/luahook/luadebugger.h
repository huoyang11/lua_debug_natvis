#ifndef __LUADEBUGGER_H__
#define __LUADEBUGGER_H__

#include "luapdb.h"
#include <unordered_map>
#include <vector>
#include <string>

//lua变量
typedef struct luavariable
{
	std::string name;		//变量名
	std::string value;		//变量值
	uint16_t type;			//变量类型
}luavariable;

//断点
typedef struct luabreakpoint
{
	std::string filepath;		//文件
	uint32_t line;				//行号
}luabreakpoint;

//调试信息结构
typedef struct luadebugger
{
	std::vector<luabreakpoint> breakpoints;				//lua断点表
	std::unordered_map<std::string, luapdb*> pdbs;		//lua总调试符号
}luadebugger;

//设置断点(缓存断点,每次加载文件时设置)
void set_bp(const std::string& filepath, uint32_t line);

//获取当前所有的局部变量
std::vector<luavariable> get_locals(lua_State* L, lua_Debug* ar);

//获取name的局部变量
luavariable get_local(lua_State* L, lua_Debug* ar,std::string name);

//获取所有的全局变量
std::vector<luavariable> get_globals(lua_State* L);

//获取name的全局变量
luavariable get_global(lua_State* L,std::string name);

//获取所有的断点
const std::vector<luabreakpoint>& get_breakpoints(struct luadebugger* debugger);

//检测断点是否存在
bool check_point(struct luadebugger* debugger,const struct luabreakpoint& bp);

//调试器函数
int debug_process(struct luadebugger* debugger);

#endif