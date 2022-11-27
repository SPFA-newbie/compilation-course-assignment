#pragma once
#ifndef FUNCTION_AND_VALUE
#define FUNCTION_AND_VALUE

#include<vector>
#include"lexic_list.h"

class BlockSentence;//前向声明 
class Expression;//前向声明

struct ValueDefine
{
	long long tag;
	int offset;
	bool isGlobal;
	bool isConst;
	ValueType type;
	void* value;
};

struct FunctionDefine
{
	long long tag;
	std::string headLable;
	ValueType returnType;
	std::vector<ValueType> paraType;
	std::vector<ValueDefine*> paraList;
	BlockSentence* virtualBlock;
	BlockSentence* block;
};

#endif