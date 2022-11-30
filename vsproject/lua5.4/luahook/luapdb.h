#ifndef __LUAPDB_H__
#define __LUAPDB_H__

#include <string>
#include <stdint.h>

typedef struct luafunpdb
{
	uint32_t baseline;			//函数起始行号
	uint32_t* lineinfos;
	uint32_t sizelineinfo;
}luafunpdb;

typedef struct luapdb
{
	struct luafunpdb main;		//主函数符号
	struct luafunpdb* childs;	//子函数符号
	uint32_t sizechild;
	std::string filepath;		//文件路径
}luapdb;

struct luapdb* create_luapdb(const std::string &filepath);

#endif