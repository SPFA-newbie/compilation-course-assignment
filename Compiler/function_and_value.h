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
	bool isConst;
	ValueType type;
	Expression* value;
};

struct FunctionDefine
{
	long long tag;
	ValueType returnType;
	std::vector<ValueType> paraType;
	BlockSentence* virtualBlock; 
	BlockSentence* block;
};

#endif