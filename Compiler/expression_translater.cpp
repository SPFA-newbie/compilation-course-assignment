#include<map>
#include<vector>

#include"asm_struct.h"
#include"translater.h"
#include"translate_tool.h"
using namespace std;

#define DefPara std::vector<ASM>& result, int offset

void compareOperatorTrans(DefPara, Symbol symbol)
{
	//获取标签
	string trueLable = getCmpLable(true);
	string falseLable = getCmpLable(false);
	//翻译
	transTo("cmp", "eax", "ebx");
	switch (symbol)
	{
		case GT:transTo("jg", trueLable, ""); break;
		case LT:transTo("jl", trueLable, ""); break;
		case GE:transTo("jge", trueLable, ""); break;
		case LE:transTo("jle", trueLable, ""); break;
		case EQ:transTo("je", trueLable, ""); break;
		case NE:transTo("jne", trueLable, ""); break;
	}
	transTo("mov", "eax", "0");
	transTo("jmp", falseLable, "");
	transTo(makeLable(trueLable), "", "");
	transTo("mov", "eax", "FFh");
	transTo(makeLable(falseLable), "", "");
	transTo("nop", "", "");
	return;
}

void operatorTrans(DefPara, Symbol symbol)
{
	switch (symbol)
	{
		case ADD:transTo("add", "eax", "ebx"); break;
		case SUB:transTo("sub", "eax", "ebx"); break;
		case MUL:transTo("imul", "eax", "ebx"); break;
		case DIV:transTo("cdp", "", "");
				 transTo("idiv", "ebx", ""); break;
		case MOD:transTo("cdp", "", "");
				 transTo("idiv", "ebx", "");
				 transTo("mov", "eax", "edx");
				 break;
		case GT:
		case LT:
		case GE:
		case LE:
		case EQ:
		case NE:compareOperatorTrans(result, offset, symbol); break;
		case LOG_AND:
		case AND:transTo("and", "eax", "ebx"); break;
		case LOG_OR:
		case OR:transTo("or", "eax", "ebx"); break;
		case XOR:transTo("xor", "eax", "ebx"); break;
	}
	return;
}

void calcExprTrans(DefPara, CalcExpr* target)
{
	//翻译
	transTo("push", "ecx", "");
	transTo("mov", "ecx", "esp");
	//翻译子表达式并将结果入栈
	for (int i = 0; i < target->sub.size(); i++)
	{
		expressionTrans(result, offset, target->sub[i]);
		transTo("push", "eax", "");
	}
	//取第一个子表达式的值
	transTo("push", "ecx", "");
	transTo("sub", "ecx", "4");
	transTo("mov", "eax", "[ecx]");
	//取后续子表达式的值并计算
	for (int i = 1; i < target->sub.size(); i++)
	{
		transTo("sub", "ecx", "4");
		transTo("mov", "ebx", "[ecx]");
		operatorTrans(result, offset, target->symbols[i - 1]);
	}
	//翻译
	transTo("pop", "ecx", "");
	transTo("mov", "esp", "ecx");
	transTo("pop", "ecx","");
	return;
}

void valueExprTrans(DefPara, ValueExpr* target)
{
	//全局
	if (target->link->isGlobal == true)
	{
		transTo("mov", "eax", offsetMake("ebp", target->link->offset));
	}else
	//非全局
	{
		transTo("mov", "eax", "[ebp-8]");
		transTo("mov", "eax", offsetMake("eax", target->link->offset));
	}
	return;
}

void tempConstExprTrans(DefPara, TempConstExpr* target)
{
	transTo("mov", "eax", valToStr((int*)target->value));
	return;
}

void recursionExprTrans(DefPara, RecursionExpr* target)
{
	//递归求表达式
	expressionTrans(result, offset, target->nextLevel);
	//取反/取负判定
	if (target->negtive == true)
		transTo("neg", "eax", "");
	else if (target->reverse == true)
		transTo("not", "eax", "");
	return;
}

void functionExprTrans(DefPara, FunctionExpr* target)
{
	sentenceTrans(result, offset, target->call);
	return;
}

void expressionTrans(DefPara, Expression* target)
{
	switch (target->type)
	{
		case CALCULATION:calcExprTrans(result, offset, (CalcExpr*)target); break;
		case VALUE:valueExprTrans(result, offset, (ValueExpr*)target); break;
		case TEMP_CONST:tempConstExprTrans(result, offset, (TempConstExpr*)target); break;
		case RECUR_EXPR:recursionExprTrans(result, offset, (RecursionExpr*)target); break;
		case FUNCTION:functionExprTrans(result, offset, (FunctionExpr*)target); break;
	}
	return;
}