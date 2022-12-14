#include<string>
#include<vector>

#include"sentence.h"
#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

#define DefPara vector<Lexic*> & target, int & pos, BlockSentence* father, Program* root

Sentence* sentenceBuilder(DefPara)
{
	//空语句
	if (checkSymbol(target[pos], END) == true)
	{
		Sentence* ret = new Sentence;
		ret->type = EMPTY_S;
		ret->father = father;
		pos++;
		return ret;
	}
	//代码块
	if (checkSymbol(target[pos], LEFT_BRA) == true)
		return blockBuilder(target, pos, father, root);
	Control* ctrl = getControl(target[pos]);
	//非控制字符：赋值或函数调用
	if (ctrl == NULL)
	{
		CustomName* name = getCustomName(target[pos]);
		if (name == NULL)throw exceptions::ISOLATED_SYMBOL;
		//赋值
		if (checkSymbol(target[pos + 1], ASSIGN) == true)
			return assignBuilder(target, pos, father, root);
		//函数调用
		else if (checkSymbol(target[pos + 1], LEFT_PARE) == true)
			return callBuilder(target, pos, father, root, true);
		//出错
		else throw exceptions::ISOLATED_SYMBOL;
	}else
	//控制字符：其他语句
	{
		//while语句
		if (ctrl->word == WHILE)return whileBuilder(target, pos, father, root); else
		//for语句
		if (ctrl->word == FOR)return forBuilder(target, pos, father, root); else
		//if语句
		if (ctrl->word == IF)return ifBuilder(target, pos, father, root); else
		//返回语句
		if (ctrl->word == RETURN)return returnBuilder(target, pos, father, root); else
		//错误情况
		throw exceptions::ISOLATED_SYMBOL;
	}
	return NULL;
}

BlockSentence* blockBuilder(DefPara)
{
	BlockSentence* ret = new BlockSentence;
	ret->type = BLOCK_S;
	ret->father = father;
	//检查左大括号
	if (checkSymbol(target[pos], LEFT_BRA) == false)throw exceptions::ISOLATED_SYMBOL;
	//读取块中代码
	pos++;
	while (checkSymbol(target[pos], RIGHT_BRA) == false)
	{
		//常量变量定义
		Control* ctrl = getControl(target[pos]);
		if (ctrl != NULL && (ctrl->word == VAR || ctrl->word == CONST))
			valueBuilder(target, pos, ret, root, false);
		//新的语句
		else if (checkSymbol(target[pos], RIGHT_BRA) == false)
			ret->children.push_back(sentenceBuilder(target, pos, ret, root));
	}
	//检查右大括号
	if (checkSymbol(target[pos], RIGHT_BRA) == false)throw exceptions::UNCLOSED_BRACKET;
	pos++;
	return ret;
}

AssignSentence* assignBuilder(DefPara)
{
	AssignSentence* ret = new AssignSentence;
	ret->type = ASSIGN_S;
	ret->father = father;
	//查找欲赋值变量
	CustomName* tarName = getCustomName(target[pos]);
	if (tarName == NULL)throw exceptions::ISOLATED_SYMBOL;
	ValueDefine* tar = getValue(tarName->name, father);
	if (tar == NULL)throw exceptions::UNDEFINED_VALUE;
	if (tar->isConst == true)throw exceptions::CHANGE_CONST;
	ret->target = tar;
	//检查赋值等号
	pos++;
	if (checkSymbol(target[pos], ASSIGN) == false)throw exceptions::ISOLATED_SYMBOL;
	//获取表达式
	pos++;
	ret->expression = expressionBuilder(target, pos, father, root);
	//检查分号
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	pos++;
	return ret;
}

WhileSentence* whileBuilder(DefPara)
{
	WhileSentence* ret = new WhileSentence;
	ret->type = WHILE_S;
	ret->father = father;
	//检查while关键字
	Control* whileCtrl = getControl(target[pos]);
	if (whileCtrl == NULL)throw exceptions::ISOLATED_SYMBOL;
	if (whileCtrl->word != WHILE)throw exceptions::ISOLATED_SYMBOL;
	//匹配左小括号
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::MISSING_CONDITION;
	//获取条件
	pos++;
	ret->condition = expressionBuilder(target, pos, father, root);
	//匹配右小括号
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//获取循环体
	pos++;
	ret->body = sentenceBuilder(target, pos, father, root);
	return ret;
}

ForSentence* forBuilder(DefPara)
{
	ForSentence* ret = new ForSentence;
	ret->type = FOR_S;
	ret->father = father;
	//检查for关键字
	Control* forCtrl = getControl(target[pos]);
	if (forCtrl == NULL)throw exceptions::ISOLATED_SYMBOL;
	if (forCtrl->word != FOR)throw exceptions::ISOLATED_SYMBOL;
	//匹配左小括号
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) != true)throw exceptions::MISSING_COUNTER;
	//获取终止条件
	pos++;
	ret->condition = expressionBuilder(target, pos, father, root);
	//匹配分号
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	//获取计数器赋值语句
	pos++;
	ret->assign = assignBuilder(target, pos, father, root);
	//匹配右小括号
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//获取循环体
	pos++;
	ret->body = sentenceBuilder(target, pos, father, root);
	return ret;
}

IfSentence* ifBuilder(DefPara)
{
	IfSentence* ret = new IfSentence;
	ret->type = IF_S;
	ret->father = father;
	//检查if关键字
	Control* ifCtrl = getControl(target[pos]);
	if (ifCtrl == NULL)throw exceptions::ISOLATED_SYMBOL;
	if (ifCtrl->word != IF)throw exceptions::ISOLATED_SYMBOL;
	//获取条件
	pos++;
	ret->condition = expressionBuilder(target, pos, father, root);
	//检查then关键字
	Control* thenCtrl = getControl(target[pos]);
	if (thenCtrl == NULL)throw exceptions::MISSING_THEN;
	if (thenCtrl->word != THEN)throw exceptions::ISOLATED_SYMBOL;
	//获取执行语句
	pos++;
	ret->body = sentenceBuilder(target, pos, father, root);
	//else处理
	Control* elseCtrl = getControl(target[pos]);
	if (elseCtrl != NULL && elseCtrl->word == ELSE)
	{
		ret->hasElse = true;
		//获取else执行语句
		pos++;
		ret->elseBody = sentenceBuilder(target, pos, father, root);
	}else
	{
		ret->hasElse = false;
		ret->elseBody = NULL;
	}
	return ret;
}

CallSentence* callBuilder(DefPara, bool isSentence)
{
	CallSentence* ret = new CallSentence;
	ret->type = CALL_S;
	ret->father = father;
	//获取欲调用的函数名
	CustomName* name = getCustomName(target[pos]);
	if (name == NULL)throw exceptions::UNDEFINED_FUNCTION;
	ret->use = getFunction(name->name, root);
	if (ret->use == NULL)throw exceptions::UNDEFINED_FUNCTION;
	//匹配左括号
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::MISSING_PARAMENT;
	//获取传入参数
	pos++;
	int paraNum = -1;
	while (checkSymbol(target[pos], RIGHT_PARE) == false)
	{
		//获取参数
		paraNum++;
		if (paraNum >= ret->use->paraType.size())throw exceptions::TOO_MANY_PARAMENT;
		ret->para.push_back(expressionBuilder(target, pos, father, root));
		//检查逗号
		if (checkSymbol(target[pos], COMMA) == true)pos++; else
		if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::ISOLATED_SYMBOL;
	}
	//检查参数数量
	if (paraNum + 1 != ret->use->paraType.size())throw exceptions::MISSING_PARAMENT;
	//检查右括号
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//检查分号
	pos++;
	if (isSentence == true)
	{
		if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
		pos++;
	}
	return ret;
}

ReturnSentence* returnBuilder(DefPara)
{
	ReturnSentence* ret=new ReturnSentence;
	ret->type = RETURN_S;
	ret->father = father;
	//检查return关键字
	Control* ctrl = getControl(target[pos]);
	if (ctrl == NULL || ctrl->word != RETURN)throw exceptions::ISOLATED_SYMBOL;
	//获取返回表达式
	pos++;
	ret->ret = expressionBuilder(target, pos, father, root);
	//检查分号
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	pos++;
	return ret;
}

#undef DefPara