#pragma once
#ifndef CONDITION
#define CONDITION

#include<vector>
#include"lexic_list.h"
#include"expression.h"

enum ConditionType
{
	RECUR_CONDIT, COMPARE, LINK
};

class Condition
{
	public:
		ConditionType type;
};

class RecursionCondit : public Condition
{
	public:
		Condition* nextLevel; 
};

class CompareCondit : public Condition
{
	public:
		Expression* left;
		Expression* right;
		Symbol symbol;
};

class LinkCondit : public Condition
{
	public:
		std::vector<Condition*> sub;
		Symbol symbol;//因为一层只存在一个优先级运算，而逻辑或、逻辑与分别是两层优先级，故一层的运算符是一样的 
}; 

#endif 