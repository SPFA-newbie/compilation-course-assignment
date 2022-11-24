#include<string>
#include<vector>

#include"sentence.h"
#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

// return -3 = 用户自定义名 
// return -2 = 常量值
// return -1 = 非表达式符号
// return 0 = 左小括号
// return 1-6 = 运算符优先级
int expressionLexicCheck(Lexic* tar)
{
	if (tar->type == CUS_NAME)return -3;
	if (tar->type == CONST_VAL)return -2;

	if (tar->type != SYMBOL)return -1;
	SymbolLexic* symbol = (SymbolLexic*)tar;
	switch (symbol->symbol)
	{
		case LEFT_PARE:return 0;
		case NEG:
		case NOT:return 1;
		case MUL:
		case DIV:
		case MOD:return 2;
		case ADD:
		case SUB:return 3;
		case AND:return 4;
		case XOR:return 5;
		case OR: return 6;
	}
	return -1;
}

#define DefPara vector<Lexic*>& target, int& pos, BlockSentence* father, Program* root
#define VecIt(T) vector<T>::iterator

ValueExpr* valueExprBuilder(DefPara);
TempConstExpr* tempExprBuilder(DefPara);
RecursionExpr* recursionExprBuilder(DefPara);
FunctionExpr* functionExprBuilder(DefPara);

//按照优先级给表达式分层
CalcExpr* calcExprLayer(vector<Expression*>& sub, vector<SymbolLexic*>& symbols);

//构造同优先级表达式
// - 符号迭代器为左闭右开区间
// - 元素迭代器为左闭右开区间，但是右端点会被替换
void calcExprBuilder
	(vector<Expression*>& sub, vector<SymbolLexic*>& symbols,
	VecIt(Expression*) exprFirst, VecIt(Expression*) exprEnd,
	VecIt(SymbolLexic*) symbolFirst, VecIt(SymbolLexic*) symbolEnd);

Expression* expressionBuilder(DefPara)
{
	//形式为：sub[i] level[i] sub[i+1]
	vector<Expression*> sub;
	vector<SymbolLexic*> symbols;
	
	//判定头部元素
	int headTag = expressionLexicCheck(target[pos]);
	if (headTag == -3)//函数或变量
	{
		//是函数
		if (expressionLexicCheck(target[pos + 1]) == 0)
			sub.push_back(functionExprBuilder(target, pos, father, root));
		//是变量
		else sub.push_back(valueExprBuilder(target, pos, father, root));
	}else if (headTag == -2)//常量值
	{
		sub.push_back(tempExprBuilder(target, pos, father, root));
	}else if (headTag == 0 || headTag == 1)//括号内子表达式
	{
		sub.push_back(recursionExprBuilder(target, pos, father, root));
	}else throw exceptions::ILLEGAL_EXPRESSION_ELEMENT;
	
	//判定其他元素
	// -- 应当为：运算符 + 子表达式的组合
	while (expressionLexicCheck(target[pos]) != -1)
	{
		//运算符判定
		int symbolLevel = expressionLexicCheck(target[pos]);
		if (symbolLevel > 0)symbols.push_back(getSymbol(target[pos]));
		else throw exceptions::ILLEGAL_OR_MISSING_OPERATOR;

		//判定下一个元素
		pos++;
		int elementTag = expressionLexicCheck(target[pos]);
		if (elementTag == -3)//函数或变量
		{
			//是函数
			if (expressionLexicCheck(target[pos + 1]) == 0)
				sub.push_back(functionExprBuilder(target, pos, father, root));
			//是常量值或变量
			else sub.push_back(valueExprBuilder(target, pos, father, root));
		}else if (elementTag == -2)//常量值
		{
			sub.push_back(tempExprBuilder(target, pos, father, root));
		}else if (elementTag == 0 || elementTag == 1)//括号内子表达式
		{
			sub.push_back(recursionExprBuilder(target, pos, father, root));
		}
		else throw exceptions::ILLEGAL_EXPRESSION_ELEMENT;
	}

	//判定是否为单元素表达式（短表达式）
	if (sub.size() == 1)return sub[0];
	//是长表达式
	return calcExprLayer(sub, symbols);
}

ValueExpr* valueExprBuilder(DefPara)
{
	//判定是否进行了定义
	CustomName* name = getCustomName(target[pos]);
	ValueDefine* val = getValue(name->name, father);
	if (val == NULL)throw exceptions::UNDEFINED_VALUE;
	//构造表达式
	ValueExpr* ret = new ValueExpr;
	ret->type = VALUE;
	ret->link = val;
	//移出当前词法元素
	pos++;
	return ret;
}

TempConstExpr* tempExprBuilder(DefPara)
{
	//词法元素转语法元素
	TempConstExpr* ret = new TempConstExpr;
	ConstValue* val = getConstValue(target[pos]);
	ret->type = TEMP_CONST;
	ret->valueType = val->valType;
	ret->value = val->value;
	//移出当前词法元素
	pos++;
	return ret;
}

RecursionExpr* recursionExprBuilder(DefPara)
{
	RecursionExpr* ret = new RecursionExpr;
	ret->type = RECUR_EXPR;
	//判定前导符号
	if (checkSymbol(target[pos], NOT) == true)//非运算符
	{
		ret->reverse = true;
		ret->negtive = false;
		pos++;
	}else if (checkSymbol(target[pos], NEG) == true)//负号
	{
		ret->reverse = false;
		ret->negtive = true;
		pos++;
	}else
	{
		ret->reverse = false;
		ret->negtive = false;
	}
	//判定左小括号
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::MISSING_BRACKET;
	//获取括号内容
	pos++;
	ret->nextLevel = expressionBuilder(target, pos, father, root);
	//判定右小括号
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//移出当前词法元素
	pos++;
	return ret;
}

FunctionExpr* functionExprBuilder(DefPara)
{
	FunctionExpr* ret = new FunctionExpr;
	ret->type = FUNCTION;
	//获取函数调用
	ret->call = callBuilder(target, pos, father, root, false);
	//callBuilder已经将语法元素移出，故不需要再移出
	return ret;
}

CalcExpr* calcExprLayer(vector<Expression*>& sub, vector<SymbolLexic*>& symbols)
{
	//对除0、1外的所有优先级进行分层
	for (int i = 2; i <= 6; i++)
	{
		VecIt(Expression*) exprIt = sub.begin();
		VecIt(SymbolLexic*) symbolIt = symbols.begin();
		while (symbolIt != symbols.end())
		{
			//寻找符合优先级的符号
			while (symbolIt != symbols.end() && expressionLexicCheck(*symbolIt) != i)
			{
				symbolIt++;
				exprIt++;
			}
			//找到了符合优先级的子表达式
			if (symbolIt != symbols.end())
			{
				VecIt(Expression*) exprBegin = exprIt;
				VecIt(SymbolLexic*) symbolBegin = symbolIt;
				//寻找这一子表达式符合优先级的尾部
				while (symbolIt != symbols.end() && expressionLexicCheck(*symbolIt) == i)
				{
					symbolIt++;
					exprIt++;
				}
				//构造子表达式
				calcExprBuilder(sub, symbols, exprBegin, exprIt, symbolBegin, symbolIt);
				//此时两个迭代器均到达了预定的位置（子表达式尾部之后）
			}
		}
	}
	if (sub.size() != 1)throw exceptions::EXPRESSION_UNNORMALIZED;
	if (sub[0]->type != CALCULATION)throw exceptions::EXPRESSION_UNNORMALIZED;
	return (CalcExpr*)sub[0];
}

void calcExprBuilder
	(vector<Expression*>& sub, vector<SymbolLexic*>& symbols,
	VecIt(Expression*) exprFirst, VecIt(Expression*) exprEnd,
	VecIt(SymbolLexic*) symbolFirst, VecIt(SymbolLexic*) symbolEnd)
{
	//构造子表达式
	CalcExpr* expr = new CalcExpr;
	expr->type = CALCULATION;
	VecIt(Expression*) exprIt = exprFirst;
	for (VecIt(SymbolLexic*) it = symbolFirst; it != symbolEnd; it++, exprIt++)
	{
		expr->symbols.push_back((*it)->symbol);
		expr->sub.push_back(*exprIt);
	}
	expr->sub.push_back(*exprEnd);

	//清理合并
	sub.erase(exprFirst, exprEnd);
	symbols.erase(symbolFirst, symbolEnd);
	*exprEnd = expr;
}

#undef VecIt(T)
#undef DefPara