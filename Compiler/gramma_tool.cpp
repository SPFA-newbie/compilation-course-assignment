#include<map>
#include<string>

#include"gramma_tool.h"
using namespace std;

ValueTypeDefine* getTypeDefine(Lexic* tar)
{
	if (tar->type != TYPE_DEF)return NULL;
	return (ValueTypeDefine*)tar;
}
Control* getControl(Lexic* tar)
{
	if (tar->type != CTRL_WORD)return NULL;
	return (Control*)tar;
}
SymbolLexic* getSymbol(Lexic* tar)
{
	if (tar->type != SYMBOL)return NULL;
	return (SymbolLexic*)tar;
}
CustomName* getCustomName(Lexic* tar)
{
	if (tar->type != CUS_NAME)return NULL;
	return (CustomName*)tar;
}
ConstValue* getConstValue(Lexic* tar)
{
	if (tar->type != CONST_VAL)return NULL;
	return (ConstValue*)tar;
}

bool checkSymbol(Lexic* tar, Symbol want)
{
	if (tar == NULL)return false;
	if (tar->type != SYMBOL)return false;
	if (((SymbolLexic*)tar)->symbol != want)return false;
	return true;
}

FunctionDefine* getFunction(string name, Program* root)
{
	std::map<string, FunctionDefine*>::iterator it = root->functions.find(name);
	if (it == root->functions.end())return NULL;
	return it->second;
}

ValueDefine* getValue(string name, BlockSentence* in)
{
	if (in == NULL)return NULL;
	std::map<string, ValueDefine*>::iterator it = in->values.find(name);
	if (it == in->values.end())return getValue(name, in->father);
	return it->second;
}

ValueDefine* createParaValue(bool isConst, ValueType type)
{
	ValueDefine* ret = new ValueDefine;
	ret->tag = getNewNUC();
	ret->isConst = isConst;
	ret->type = type;
	return ret;
}