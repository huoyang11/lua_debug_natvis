#ifndef __LUADEBUGGER_H__
#define __LUADEBUGGER_H__

#include "luapdb.h"
#include <unordered_map>
#include <string>

typedef struct luabreackpoint
{
	std::string filepath;		//文件
	uint32_t line;				//行号
}luabreackpoint;

typedef struct luadebugger
{
	std::unordered_map<std::string, luapdb*> pdbs;		//lua总调试符号
}luadebugger;

//设置断点(缓存断点,每次加载文件时设置)
void set_bp(const std::string& filepath, uint32_t line);

#endif