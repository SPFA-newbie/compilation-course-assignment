#include<string>
#include<vector>

#include"sentence.h"
#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

// return -3 = �û��Զ����� 
// return -2 = ����ֵ
// return -1 = �Ǳ��ʽ����
// return 0 = ��С����
// return 1-6 = ��������ȼ�
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

//�������ȼ������ʽ�ֲ�
CalcExpr* calcExprLayer(vector<Expression*>& sub, vector<SymbolLexic*>& symbols);

//����ͬ���ȼ����ʽ
// - ���ŵ�����Ϊ����ҿ�����
// - Ԫ�ص�����Ϊ����ҿ����䣬�����Ҷ˵�ᱻ�滻
void calcExprBuilder
	(vector<Expression*>& sub, vector<SymbolLexic*>& symbols,
	VecIt(Expression*) exprFirst, VecIt(Expression*) exprEnd,
	VecIt(SymbolLexic*) symbolFirst, VecIt(SymbolLexic*) symbolEnd);

Expression* expressionBuilder(DefPara)
{
	//��ʽΪ��sub[i] level[i] sub[i+1]
	vector<Expression*> sub;
	vector<SymbolLexic*> symbols;
	
	//�ж�ͷ��Ԫ��
	int headTag = expressionLexicCheck(target[pos]);
	if (headTag == -3)//���������
	{
		//�Ǻ���
		if (expressionLexicCheck(target[pos + 1]) == 0)
			sub.push_back(functionExprBuilder(target, pos, father, root));
		//�Ǳ���
		else sub.push_back(valueExprBuilder(target, pos, father, root));
	}else if (headTag == -2)//����ֵ
	{
		sub.push_back(tempExprBuilder(target, pos, father, root));
	}else if (headTag == 0 || headTag == 1)//�������ӱ��ʽ
	{
		sub.push_back(recursionExprBuilder(target, pos, father, root));
	}else throw exceptions::ILLEGAL_EXPRESSION_ELEMENT;
	
	//�ж�����Ԫ��
	// -- Ӧ��Ϊ������� + �ӱ��ʽ�����
	while (expressionLexicCheck(target[pos]) != -1)
	{
		//������ж�
		int symbolLevel = expressionLexicCheck(target[pos]);
		if (symbolLevel > 0)symbols.push_back(getSymbol(target[pos]));
		else throw exceptions::ILLEGAL_OR_MISSING_OPERATOR;

		//�ж���һ��Ԫ��
		pos++;
		int elementTag = expressionLexicCheck(target[pos]);
		if (elementTag == -3)//���������
		{
			//�Ǻ���
			if (expressionLexicCheck(target[pos + 1]) == 0)
				sub.push_back(functionExprBuilder(target, pos, father, root));
			//�ǳ���ֵ�����
			else sub.push_back(valueExprBuilder(target, pos, father, root));
		}else if (elementTag == -2)//����ֵ
		{
			sub.push_back(tempExprBuilder(target, pos, father, root));
		}else if (elementTag == 0 || elementTag == 1)//�������ӱ��ʽ
		{
			sub.push_back(recursionExprBuilder(target, pos, father, root));
		}
		else throw exceptions::ILLEGAL_EXPRESSION_ELEMENT;
	}

	//�ж��Ƿ�Ϊ��Ԫ�ر��ʽ���̱��ʽ��
	if (sub.size() == 1)return sub[0];
	//�ǳ����ʽ
	return calcExprLayer(sub, symbols);
}

ValueExpr* valueExprBuilder(DefPara)
{
	//�ж��Ƿ�����˶���
	CustomName* name = getCustomName(target[pos]);
	ValueDefine* val = getValue(name->name, father);
	if (val == NULL)throw exceptions::UNDEFINED_VALUE;
	//������ʽ
	ValueExpr* ret = new ValueExpr;
	ret->type = VALUE;
	ret->link = val;
	//�Ƴ���ǰ�ʷ�Ԫ��
	pos++;
	return ret;
}

TempConstExpr* tempExprBuilder(DefPara)
{
	//�ʷ�Ԫ��ת�﷨Ԫ��
	TempConstExpr* ret = new TempConstExpr;
	ConstValue* val = getConstValue(target[pos]);
	ret->type = TEMP_CONST;
	ret->valueType = val->valType;
	ret->value = val->value;
	//�Ƴ���ǰ�ʷ�Ԫ��
	pos++;
	return ret;
}

RecursionExpr* recursionExprBuilder(DefPara)
{
	RecursionExpr* ret = new RecursionExpr;
	ret->type = RECUR_EXPR;
	//�ж�ǰ������
	if (checkSymbol(target[pos], NOT) == true)//�������
	{
		ret->reverse = true;
		ret->negtive = false;
		pos++;
	}else if (checkSymbol(target[pos], NEG) == true)//����
	{
		ret->reverse = false;
		ret->negtive = true;
		pos++;
	}else
	{
		ret->reverse = false;
		ret->negtive = false;
	}
	//�ж���С����
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::MISSING_BRACKET;
	//��ȡ��������
	pos++;
	ret->nextLevel = expressionBuilder(target, pos, father, root);
	//�ж���С����
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//�Ƴ���ǰ�ʷ�Ԫ��
	pos++;
	return ret;
}

FunctionExpr* functionExprBuilder(DefPara)
{
	FunctionExpr* ret = new FunctionExpr;
	ret->type = FUNCTION;
	//��ȡ��������
	ret->call = callBuilder(target, pos, father, root, false);
	//callBuilder�Ѿ����﷨Ԫ���Ƴ����ʲ���Ҫ���Ƴ�
	return ret;
}

CalcExpr* calcExprLayer(vector<Expression*>& sub, vector<SymbolLexic*>& symbols)
{
	//�Գ�0��1����������ȼ����зֲ�
	for (int i = 2; i <= 6; i++)
	{
		VecIt(Expression*) exprIt = sub.begin();
		VecIt(SymbolLexic*) symbolIt = symbols.begin();
		while (symbolIt != symbols.end())
		{
			//Ѱ�ҷ������ȼ��ķ���
			while (symbolIt != symbols.end() && expressionLexicCheck(*symbolIt) != i)
			{
				symbolIt++;
				exprIt++;
			}
			//�ҵ��˷������ȼ����ӱ��ʽ
			if (symbolIt != symbols.end())
			{
				VecIt(Expression*) exprBegin = exprIt;
				VecIt(SymbolLexic*) symbolBegin = symbolIt;
				//Ѱ����һ�ӱ��ʽ�������ȼ���β��
				while (symbolIt != symbols.end() && expressionLexicCheck(*symbolIt) == i)
				{
					symbolIt++;
					exprIt++;
				}
				//�����ӱ��ʽ
				calcExprBuilder(sub, symbols, exprBegin, exprIt, symbolBegin, symbolIt);
				//��ʱ������������������Ԥ����λ�ã��ӱ��ʽβ��֮��
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
	//�����ӱ��ʽ
	CalcExpr* expr = new CalcExpr;
	expr->type = CALCULATION;
	VecIt(Expression*) exprIt = exprFirst;
	for (VecIt(SymbolLexic*) it = symbolFirst; it != symbolEnd; it++, exprIt++)
	{
		expr->symbols.push_back((*it)->symbol);
		expr->sub.push_back(*exprIt);
	}
	expr->sub.push_back(*exprEnd);

	//����ϲ�
	sub.erase(exprFirst, exprEnd);
	symbols.erase(symbolFirst, symbolEnd);
	*exprEnd = expr;
}

#undef VecIt(T)
#undef DefPara