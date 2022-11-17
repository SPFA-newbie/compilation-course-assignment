#pragma once
#ifndef PROGRAM_STRUCT
#define PROGRAM_STRUCT

#include<map>
#include<string>
#include<vector>
#include"sentence.h"
#include"lexic_list.h"
#include"function_and_value.h"

class Program
{
	public:
		BlockSentence* virtualBlock;//用于存储全局变量 
		std::map<std::string, FunctionDefine*> functions;
		BlockSentence* main;
};

#endif