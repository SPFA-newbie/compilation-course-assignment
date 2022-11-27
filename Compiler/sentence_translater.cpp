#include<map>
#include<vector>

#include"asm_struct.h"
#include"translater.h"
#include"translate_tool.h"
using namespace std;

#define DefPara std::vector<ASM>& result, int offset

void blockTrans(DefPara, BlockSentence* target)
{
	//变量入栈
	map<std::string, ValueDefine*>::iterator it = target->values.begin();
	for (; it != target->values.end(); it++)
	{
		offset += 4;
		it->second->offset = offset;
		transTo("mov", "eax", valToStr((int*)it->second->value));
		transTo("push", "eax", "");
	}
	//翻译
	transTo("push", "ecx", "");
	transTo("mov", "ecx", "esp");
	//子语句翻译
	for (int i = 0; i < target->children.size(); i++)
		sentenceTrans(result, offset, target->children[i]);
	//翻译
	transTo("mov", "esp", "ecx");
	transTo("pop", "ecx", "");
	return;
}

void assignTrans(DefPara, AssignSentence* target)
{
	//计算表达式的值
	expressionTrans(result, offset, target->expression);
	//全局变量赋值
	if (target->target->isGlobal == true)
	{
		transTo("mov", offsetMake("ebp", target->target->offset), "eax");
	}
	else
	{
		transTo("mov", "ebx", "[ebp-8]");
		transTo("mov", offsetMake("ebx", target->target->offset), "eax");
	}
	return;
}

void returnTrans(DefPara, ReturnSentence* target)
{
	//计算返回值
	expressionTrans(result, offset, target->ret);
	//获取原栈顶并获取返回地址
	transTo("mov", "esp", "[ebp-8]");
	transTo("pop", "ecx", "");
	transTo("pop", "ebx", "");
	transTo("mov", "[ebp-8]", "ebx");
	//卸载传入的参数
	transTo("mov", "esp", "[ebp-4]");
	transTo("pop", "ebx", "");
	transTo("mov", "[ebp-4]", "ebx");
	//返回
	transTo("mov", "eip", "ecx");
	return;
}
void callTrans(DefPara, CallSentence* target)
{
	//翻译
	transTo("mov", "ebx", "[ebp-4]");
	transTo("push", "ebx", "");
	transTo("mov", "[ebp-4]", "esp");
	//计算参数并入栈
	for (int i = 0; i < target->para.size(); i++)
	{
		expressionTrans(result, offset, target->para[i]);
		transTo("push", "eax", "");
	}
	//翻译
	transTo("mov", "eax", "[ebp-8]");
	transTo("push", "eax", "");
	transTo("push", "eip", "");
	transTo("jmp", target->use->headLable, "");
	return;
}

void whileTrans(DefPara, WhileSentence* target)
{
	//获取标签
	string headLable = getWhileLable(true);
	string endLable = getWhileLable(false);
	//翻译
	transTo(makeLable(headLable), "", "");
	//条件判断与跳转
	expressionTrans(result, offset, target->condition);
	transTo("test", "eax", "FFh");
	transTo("jz", endLable, "");
	//循环体
	sentenceTrans(result, offset, target->body);
	//翻译
	transTo("jmp", headLable, "");
	transTo(makeLable(endLable), "", "");
	transTo("nop", "", "");
	return;
}

void forTrans(DefPara, ForSentence* target)
{
	//获取标签
	string headLable = getForLable(true);
	string endLable = getForLable(false);
	//翻译
	transTo(makeLable(headLable), "", "");
	//条件判断与跳转
	expressionTrans(result, offset, target->condition);
	transTo("test", "eax", "FFh");
	transTo("jz", endLable, "");
	//循环体
	sentenceTrans(result, offset, target->body);
	//循环量计算
	sentenceTrans(result, offset, target->assign);
	//翻译
	transTo("jmp", headLable, "");
	transTo(makeLable(endLable), "", "");
	transTo("nop", "", "");
	return;
}

void ifTrans(DefPara, IfSentence* target)
{
	//获取标签
	string elseLable = getIfLable(true);
	string endLable = getIfLable(false);
	//条件判断和跳转
	expressionTrans(result, offset, target->condition);
	transTo("test", "eax", "FFh");
	transTo("jz", elseLable, "");
	//为真时执行
	sentenceTrans(result, offset, target->body);
	transTo("jmp", endLable, "");
	//为假时执行
	transTo(makeLable(elseLable), "", "");
	if (target->hasElse == false)
		transTo("nop", "", "");
	else sentenceTrans(result, offset, target->elseBody);
	//尾部
	transTo(makeLable(endLable), "", "");
	transTo("nop", "", "");
	return;
}

void sentenceTrans(DefPara, Sentence* target)
{
	switch (target->type)
	{
		case BLOCK_S:blockTrans(result, offset, (BlockSentence*)target); break;
		case ASSIGN_S:assignTrans(result, offset, (AssignSentence*)target); break;
		case RETURN_S:returnTrans(result, offset, (ReturnSentence*)target); break;
		case CALL_S:callTrans(result, offset, (CallSentence*)target); break;
		case WHILE_S:whileTrans(result, offset, (WhileSentence*)target); break;
		case FOR_S:forTrans(result, offset, (ForSentence*)target); break;
		case IF_S:ifTrans(result, offset, (IfSentence*)target); break;
		case EMPTY_S:transTo("nop","",""); break;
	}
	return;
}

#undef DefPara