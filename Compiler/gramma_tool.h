#pragma once
#ifndef GRAMMA_TOOL
#define GRAMMA_TOOL

#include"sentence.h"
#include"lexic_list.h"
#include"program_struct.h"
#include"function_and_value.h"

static long long NUC = 0;//名称统一编码
static inline long long getNewNUC()
{
	NUC++;
	return NUC;
}

ValueTypeDefine* getTypeDefine(Lexic* tar);
Control* getControl(Lexic* tar);
SymbolLexic* getSymbol(Lexic* tar);
CustomName* getCustomName(Lexic* tar);
ConstValue* getConstValue(Lexic* tar);

bool checkSymbol(Lexic* tar, Symbol want);

FunctionDefine* getFunction(std::string name, Program* root);
ValueDefine* getValue(std::string name, BlockSentence* in);

ValueDefine* createParaValue(bool isConst, ValueType type);//仅用于函数的参数表

#endif