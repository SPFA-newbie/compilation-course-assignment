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
	std::string out()
	{
		std::string ret = comm;
		if (para1 != "")ret.append(" ");
		ret.append(para1);
		if (para2 != "")ret.append(", ");
		ret.append(para2);
		return ret;
	}
};

#endif