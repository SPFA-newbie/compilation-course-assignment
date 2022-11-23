#include<string>
#include<vector>

#include"sentence.h"
#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

// return -1 = �Ǳ��ʽ����
// return 0 = ��С����
// return 1-6 = ��������ȼ�
// return 7 = �û��Զ����� 
// return 8 = ����ֵ
int expressionLexicCheck(Lexic* tar)
{
	if (tar->type == CUS_NAME)return 7;
	if (tar->type == CONST_VAL)return 8;

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

Expression* expressionBuilder(vector<Lexic*>& target, int& pos, BlockSentence* father, Program* root)
{
	vector<Expression*> sub;
	vector<int> level;
	//�ж�ͷ��Ԫ��
	int headTag = expressionLexicCheck(target[pos]);
	if (headTag == 7)//�������������ֵ
	{

	}else if (headTag == 0 || headTag == 1)//�������ӱ��ʽ
	{

	}else throw exceptions::ILLEGAL_EXPRESSION_HEAD;

}

#define DefPara vector<Lexic*> & target, int & pos, int end, BlockSentence* father, Program* root

#undef DefPara