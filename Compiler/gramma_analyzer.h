#pragma once
#ifndef GRAMMA_ANALYZER
#define GRAMMA_ANALYZER

#include"sentence.h"
#include"condition.h"
#include"expression.h"
#include"program_struct.h"
#include"function_and_value.h"

#define DefPara std::vector<Lexic*> & target, int & pos

Program* programBuilder(DefPara);
void functionBuilder(DefPara, Program* root);
void valueBuilder(DefPara, BlockSentence* father, Program* root);
//----------------------------------------------------------------------------

Sentence* sentenceBuilder(DefPara, BlockSentence* father, Program* root);

BlockSentence* blockBuilder(DefPara, BlockSentence* father, Program* root);
AssignSentence* assignBuilder(DefPara, BlockSentence* father, Program* root);
WhileSentence* whileBuilder(DefPara, BlockSentence* father, Program* root);
ForSentence* forBuilder(DefPara, BlockSentence* father, Program* root);
IfSentence* ifBuilder(DefPara, BlockSentence* father, Program* root);

CallSentence* callBuilder(DefPara, BlockSentence* father, Program* root, bool isSentence);
ReturnSentence* returnBuilder(DefPara, BlockSentence* father,Program* root);
//-----------------------------------------------------------------------------

Expression* expressionBuilder(DefPara, BlockSentence* father, Program* root);

ValueExpr* valueExprBuilder(DefPara, int end, BlockSentence* father, Program* root);
RecursionExpr* recursionExprBuilder(DefPara, int end, BlockSentence* father, Program* root);
FunctionExpr* functionExprBuilder(DefPara, int end, BlockSentence* father, Program* root);
CalcExpr* calcExprBuilder(DefPara, int end, BlockSentence* father, Program* root);
//-----------------------------------------------------------------------------

Condition* conditionBuilder(DefPara, BlockSentence* father, Program* root);

RecursionCondit* recurConditBuilder(DefPara, int end, BlockSentence* father, Program* root);
CompareCondit* compareConditBuilder(DefPara, int end, BlockSentence* father, Program* root);
LinkCondit* linkConditBuilder(DefPara, int end, BlockSentence* father, Program* root);
#undef DefPara

#endif