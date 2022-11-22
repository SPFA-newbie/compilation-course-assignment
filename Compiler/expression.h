#pragma once
#ifndef EXPRESSION
#define EXPRESSION

#include<vector>
#include"lexic_list.h"
#include"function_and_value.h"

class CallSentence;//前向声明 

enum ExpressionType
{
	VALUE, RECUR_EXPR, FUNCTION, CALCULATION
}; 

class Expression
{
	public:
		ExpressionType type;
};

class ValueExpr : public Expression
{
	public:
		ValueDefine* link;
};

class RecursionExpr : public Expression
{
	public:
		bool negtive;//标明是否存在负号 
		bool reverse;//标明是否进行了非运算 
		Expression* nextLevel;
};

class FunctionExpr : public Expression
{
	public:
		CallSentence* call;
};

class CalcExpr : public Expression
{
	public:
		std::vector<Expression*> sub;
		std::vector<Symbol> symbol;
};

#endif
