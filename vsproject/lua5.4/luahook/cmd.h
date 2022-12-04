#ifndef __CMD_H__
#define __CMD_H__

#include <string>
#include <vector>
#include <unordered_map>

typedef std::string (*cmd_function)(const std::vector<std::string> &cmds);

typedef struct lua_cmd{
	uint16_t type;
	cmd_function fun;
	std::string cmd_name;
}lua_cmd;

std::vector<std::string> parse_cmd(const std::string& str);

#endif