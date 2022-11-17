#include<string>
#include<vector>

#include"sentence.h"
#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

#define DefPara vector<Lexic*> & target, int & pos, BlockSentence* father, Program* root

Sentence* sentenceBuilder(DefPara)
{
	//�����
	if (checkSymbol(target[pos], END) == true)
	{
		Sentence* ret = new Sentence;
		ret->type = EMPTY_S;
		ret->father = father;
		pos++;
		return ret;
	}
	//�����
	if (checkSymbol(target[pos], LEFT_BRA) == true)
		return blockBuilder(target, pos, father, root);
	Control* ctrl = getControl(target[pos]);
	//�ǿ����ַ�����ֵ��������
	if (ctrl == NULL)
	{
		CustomName* name = getCustomName(target[pos]);
		if (name == NULL)throw exceptions::ISOLATED_SYMBOL;
		//��ֵ
		if (checkSymbol(target[pos + 1], ASSIGN) == true)
			return assignBuilder(target, pos, father, root);
		//��������
		else if (checkSymbol(target[pos + 1], LEFT_PARE) == true)
			return callBuilder(target, pos, father, root, true);
		//����
		else throw exceptions::ISOLATED_SYMBOL;
	}else
	//�����ַ����������
	{
		//while���
		if (ctrl->word == WHILE)return whileBuilder(target, pos, father, root); else
		//for���
		if (ctrl->word == FOR)return forBuilder(target, pos, father, root); else
		//if���
		if (ctrl->word == IF)return ifBuilder(target, pos, father, root); else
		//�������
		if (ctrl->word == RETURN)return returnBuilder(target, pos, father, root); else
		//�������
		throw exceptions::ISOLATED_SYMBOL;
	}
	return NULL;
}

BlockSentence* blockBuilder(DefPara)
{
	BlockSentence* ret = new BlockSentence;
	ret->type = BLOCK_S;
	ret->father = father;
	//����������
	if (checkSymbol(target[pos], LEFT_BRA) == false)throw exceptions::ISOLATED_SYMBOL;
	//��ȡ���д���
	pos++;
	while (checkSymbol(target[pos], RIGHT_BRA) == false)
	{
		//������������
		Control* ctrl = getControl(target[pos]);
		if (ctrl != NULL && (ctrl->word == VAR || ctrl->word == CONST))
			valueBuilder(target, pos, ret, root);
		//�µ����
		else if (checkSymbol(target[pos], RIGHT_BRA) == false)
			ret->children.push_back(sentenceBuilder(target, pos, ret, root));
	}
	//����Ҵ�����
	if (checkSymbol(target[pos], RIGHT_BRA) == false)throw exceptions::UNCLOSED_BRACKET;
	pos++;
	return ret;
}

AssignSentence* assignBuilder(DefPara)
{
	AssignSentence* ret = new AssignSentence;
	ret->type = ASSIGN_S;
	ret->father = father;
	//��������ֵ����
	CustomName* tarName = getCustomName(target[pos]);
	if (tarName == NULL)throw exceptions::ISOLATED_SYMBOL;
	ValueDefine* tar = getValue(tarName->name, father);
	if (tar == NULL)throw exceptions::UNDEFINED_VALUE;
	if (tar->isConst == true)throw exceptions::CHANGE_CONST;
	ret->target = tar;
	//��鸳ֵ�Ⱥ�
	pos++;
	if (checkSymbol(target[pos], ASSIGN) == false)throw exceptions::ISOLATED_SYMBOL;
	//��ȡ���ʽ
	pos++;
	ret->expression = expressionBuilder(target, pos, father, root);
	//���ֺ�
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	pos++;
	return ret;
}

WhileSentence* whileBuilder(DefPara)
{
	WhileSentence* ret = new WhileSentence;
	ret->type = WHILE_S;
	ret->father = father;
	//���while�ؼ���
	Control* whileCtrl = getControl(target[pos]);
	if (whileCtrl == NULL)throw exceptions::ISOLATED_SYMBOL;
	if (whileCtrl->word != WHILE)throw exceptions::ISOLATED_SYMBOL;
	//ƥ����С����
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::MISSING_CONDITION;
	//��ȡ����
	pos++;
	ret->condition = conditionBuilder(target, pos, father, root);
	//ƥ����С����
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//��ȡѭ����
	pos++;
	ret->body = sentenceBuilder(target, pos, father, root);
	return ret;
}

ForSentence* forBuilder(DefPara)
{
	ForSentence* ret = new ForSentence;
	ret->type = FOR_S;
	ret->father = father;
	//���for�ؼ���
	Control* forCtrl = getControl(target[pos]);
	if (forCtrl == NULL)throw exceptions::ISOLATED_SYMBOL;
	if (forCtrl->word != FOR)throw exceptions::ISOLATED_SYMBOL;
	//ƥ����С����
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) != true)throw exceptions::MISSING_COUNTER;
	//��ȡ��ֹ����
	pos++;
	ret->condition = conditionBuilder(target, pos, father, root);
	//ƥ��ֺ�
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	//��ȡ��������ֵ���
	pos++;
	ret->assign = assignBuilder(target, pos, father, root);
	//ƥ����С����
	if (checkSymbol(target[pos], RIGHT_PARE) == false)throw exceptions::UNCLOSED_BRACKET;
	//��ȡѭ����
	pos++;
	ret->body = sentenceBuilder(target, pos, father, root);
	return ret;
}

IfSentence* ifBuilder(DefPara)
{
	IfSentence* ret = new IfSentence;
	ret->type = IF_S;
	ret->father = father;
	//���if�ؼ���
	Control* ifCtrl = getControl(target[pos]);
	if (ifCtrl == NULL)throw exceptions::ISOLATED_SYMBOL;
	if (ifCtrl->word != IF)throw exceptions::ISOLATED_SYMBOL;
	//��ȡ
}

#undef DefPara