#pragma once
#ifndef TRANSLATER
#define TRANSLATER

#include<vector>
#include"asm_struct.h"
#include"program_struct.h"

#define DefPara std::vector<ASM>& result, int offset

void programTrans(DefPara, Program* target);

void functionTrans(DefPara, FunctionDefine* target);

void expressionTrans(DefPara, Expression* target);
void calcExprTrans(DefPara, CalcExpr* target);
void valueExprTrans(DefPara, ValueExpr* target);
void tempConstExprTrans(DefPara, TempConstExpr* target);
void recursionExprTrans(DefPara, RecursionExpr* target);
void functionExprTrans(DefPara, FunctionExpr* target);

void sentenceTrans(DefPara, Sentence* target);

#undef DefPara

#endif