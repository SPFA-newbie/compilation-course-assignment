#include<string>
#include<vector>

#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

#define DefPara vector<Lexic*> & target, int & pos

Program* programBuilder(DefPara)
{
	Program* ret=new Program;
	ret->virtualBlock=new BlockSentence;
	ret->virtualBlock->father = NULL;
	while(pos!=target.size())
	{
		if (target[pos]->type == TYPE_DEF)//定义函数
			functionBuilder(target, pos, ret);
		else if (target[pos]->type == CTRL_WORD && (((Control*)target[pos])->word == VAR || ((Control*)target[pos])->word == CONST))//定义值
			valueBuilder(target, pos, ret->virtualBlock, ret, true);
		else if (target[pos]->type == SYMBOL && ((SymbolLexic*)target[pos])->symbol == LEFT_BRA)
			ret->main = blockBuilder(target, pos, ret->virtualBlock, ret);
		else throw exceptions::ISOLATED_SYMBOL;
	}
	return ret;
}

void functionBuilder(DefPara, Program* root)
{
	FunctionDefine* fun = new FunctionDefine;
	fun->virtualBlock = new BlockSentence;
	fun->virtualBlock->father = root->virtualBlock;
	//读取函数返回值类型
	fun->returnType = getTypeDefine(target[pos])->valType;
	//读取函数定义的名称
	pos++;
	CustomName* funName = getCustomName(target[pos]);
	if (funName == NULL)throw exceptions::ILLEGAL_FUNCTION;
	if (getFunction(funName->name, root) != NULL)throw exceptions::DUPLICATE_FUNCTION;
	fun->tag = getNewNUC();
	//读取左括号
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::ISOLATED_SYMBOL;
	//读取参数表
	pos++;
	while (checkSymbol(target[pos], RIGHT_PARE) == false)
	{
		//参数类型
		ValueTypeDefine* paraType = getTypeDefine(target[pos]);
		if (paraType == NULL)throw exceptions::ISOLATED_SYMBOL;
		//参数名称
		pos++;
		CustomName* paraName = getCustomName(target[pos]);
		if (getValue(paraName->name, fun->virtualBlock) != NULL)throw exceptions::DUPLICATE_VALUE;
		//创建参数
		ValueDefine* value = createParaValue(false, paraType->valType);
		value->value = NULL;
		fun->virtualBlock->values[paraName->name] = value;
		//保存参数类型
		fun->paraType.push_back(paraType->valType);
		//保存参数指针
		fun->paraList.push_back(value);
		//检查符号
		pos++;
		if (checkSymbol(target[pos], COMMA) == true)pos++; else
		if (checkSymbol(target[pos], RIGHT_PARE) != true)throw exceptions::ISOLATED_SYMBOL;
	}
	//读取代码块
	pos++;
	if (checkSymbol(target[pos], LEFT_BRA) == false)throw exceptions::ISOLATED_SYMBOL;
	fun->block = blockBuilder(target, pos, fun->virtualBlock, root);
	//添加到定义中
	root->functions[funName->name] = fun;
	return;
}

void valueBuilder(DefPara, BlockSentence* father, Program* root, bool isGlobal)
{
	ValueDefine* value = new ValueDefine;
	value->isGlobal = isGlobal;
	//确定变量常量
	if (getControl(target[pos])->word == VAR)value->isConst = false;
		else value->isConst = true;
	//确定类型
	pos++;
	ValueTypeDefine* type = getTypeDefine(target[pos]);
	if (type == NULL)throw exceptions::MISSING_TYPE_DEFINE;
	value->type = type->valType;
	//确定名称
	pos++;
	CustomName* name = getCustomName(target[pos]);
	if (name == NULL)throw::exceptions::ILLEGAL_VALUE;
	if (getValue(name->name, father) != NULL)throw exceptions::DUPLICATE_VALUE;
	value->tag = getNewNUC();
	//赋值符号检测
	pos++;
	if (checkSymbol(target[pos], ASSIGN) == false)throw exceptions::UNINIT_VALUE;
	//获取赋值
	pos++;
	if (target[pos]->type != CONST_VAL)throw exceptions::ILLEGAL_INIT_VALUE;
	value->value = getConstValue(target[pos])->value;
	//分号检测
	pos++;
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	pos++;
	//添加到定义中
	father->values[name->name] = value;
	return;
}

#undef DefType