#pragma once
#ifndef LEXIC_LIST
#define LEXIC_LIST

#include<string>

enum LexicType{
	
	CUS_NAME,//自定义名
	CONST_VAL,//常量值
	TYPE_DEF,//类型定义
	CTRL_WORD,//流程控制
	SYMBOL//符号
};
enum ValueType{
	//整数类型符 
	SHORT, INT, LONG,
	//浮点数类型符
	FLOAT, DOUBLE,
	//字符（串）类型符
	CHAR,STRING, 
	//无类型
	VOID
}; 
enum CtrlWord{
	//分支
	IF, THEN, ELSE,
	//循环
	WHILE, FOR,
	//流程控制
	CONTINUE, BREAK,
	//其他 
	CONST, RETURN, VAR
};
enum Symbol{
	//运算符
	AND,		//	&			0
	OR,			//	|			1
	NOT,		//	!			2
	XOR,		//	^			3
	ADD,		//	+			4
	SUB,		//	-			5
	MUL,		//	*			6
	DIV,		//	/			7
	MOD,		//	%			8
	NEG,		//	$代替负号 	9
	LOG_AND,	//	&&			10
	LOG_OR,		//	||			11
	LT,			//	<			12
	GT,			//	>			13
	EQ,			//	==			14
	NE,			//	!=			15
	GE,			//	>=			16
	LE,			//	<=			17
	ASSIGN,		//	=			18
	//括号与分隔符 
	LEFT_BRA,	//	{			19
	RIGHT_BRA,	//	}			20
	LEFT_SQU,	//	[			21
	RIGHT_SQU,	//	]			22
	LEFT_PARE,	//	(			23
	RIGHT_PARE,	//	)			24
	END,		//	;			25
	COMMA		//	, 			26
};

class Lexic
{
	public:
		LexicType type;
};
class ValueTypeDefine : public Lexic
{
	public:
		ValueType valType; 
};
class Control : public Lexic
{
	public:
		CtrlWord word;
}; 
class SymbolLexic : public Lexic
{
	public:
		Symbol symbol;
};
class CustomName : public Lexic
{
	public:
		std::string name;
};

class ConstValue : public Lexic
{
	public:
		ValueType valType;
		void* value;
};

#endif