#pragma once
#ifndef SENTENCE
#define SENTENCE

#include<map>
#include<string>
#include<vector> 
#include"expression.h" 
#include"function_and_value.h"

enum SentenceType
{
	BLOCK_S,ASSIGN_S,WHILE_S,FOR_S,IF_S,CALL_S,RETURN_S,EMPTY_S
};

class Sentence
{
	public:
		SentenceType type;
		BlockSentence* father;
};

class BlockSentence : public Sentence
{
	public:
		std::map<std::string, ValueDefine*> values;
		std::vector<Sentence*> children;
};

class AssignSentence : public Sentence
{
	public:
		ValueDefine* target;
		Expression* expression;
};

class WhileSentence : public Sentence
{
	public:
		Expression* condition;
		Sentence* body;
};

class ForSentence : public Sentence
{
	public:
		Expression* condition;
		AssignSentence* assign;
		Sentence* body;
};

class IfSentence : public Sentence
{
	public:
		bool hasElse;
		Expression* condition;
		Sentence* body;
		Sentence* elseBody;
};

class CallSentence : public Sentence
{
	public:
		FunctionDefine* use;
		std::vector<Expression*> para;
};

class ReturnSentence : public Sentence
{
	public:
		Expression* ret;
};
#endif