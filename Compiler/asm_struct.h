#pragma once
#ifndef ASM_STRUCT
#define ASM_STRUCT

#include<string>

struct ASM
{
	std::string comm, para1, para2;
	ASM(std::string comm, std::string para1, std::string para2)
	{
		this->comm = comm;
		this->para1 = para1;
		this->para2 = para2;
	}
};

#endif