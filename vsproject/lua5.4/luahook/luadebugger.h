#ifndef __LUADEBUGGER_H__
#define __LUADEBUGGER_H__

#include "luapdb.h"
#include <unordered_map>
#include <string>

typedef struct luadebugger
{
	std::unordered_map<std::string, luapdb*> pdbs;		//lua总调试符号
}luadebugger;

#endif