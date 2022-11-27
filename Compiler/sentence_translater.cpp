#include<map>
#include<vector>

#include"asm_struct.h"
#include"translater.h"
#include"translate_tool.h"
using namespace std;

#define DefPara std::vector<ASM>& result, int offset

void blockTrans(DefPara, BlockSentence* target)
{
	//������ջ
	map<std::string, ValueDefine*>::iterator it = target->values.begin();
	for (; it != target->values.end(); it++)
	{
		offset += 4;
		it->second->offset = offset;
		transTo("mov", "eax", valToStr((int*)it->second->value));
		transTo("push", "eax", "");
	}
	//����
	transTo("push", "ecx", "");
	transTo("mov", "ecx", "esp");
	//����䷭��
	for (int i = 0; i < target->children.size(); i++)
		sentenceTrans(result, offset, target->children[i]);
	//����
	transTo("mov", "esp", "ecx");
	transTo("pop", "ecx", "");
	return;
}

void assignTrans(DefPara, AssignSentence* target)
{
	//������ʽ��ֵ
	expressionTrans(result, offset, target->expression);
	//ȫ�ֱ�����ֵ
	if (target->target->isGlobal == true)
	{
		transTo("mov", offsetMake("ebp", target->target->offset), "eax");
	}
	else
	{
		transTo("mov", "ebx", "[ebp-8]");
		transTo("mov", offsetMake("ebx", target->target->offset), "eax");
	}
	return;
}

void returnTrans(DefPara, ReturnSentence* target)
{
	//���㷵��ֵ
	expressionTrans(result, offset, target->ret);
	//��ȡԭջ������ȡ���ص�ַ
	transTo("mov", "esp", "[ebp-8]");
	transTo("pop", "ecx", "");
	transTo("pop", "ebx", "");
	transTo("mov", "[ebp-8]", "ebx");
	//ж�ش���Ĳ���
	transTo("mov", "esp", "[ebp-4]");
	transTo("pop", "ebx", "");
	transTo("mov", "[ebp-4]", "ebx");
	//����
	transTo("mov", "eip", "ecx");
	return;
}
void callTrans(DefPara, CallSentence* target)
{
	//����
	transTo("mov", "ebx", "[ebp-4]");
	transTo("push", "ebx", "");
	transTo("mov", "[ebp-4]", "esp");
	//�����������ջ
	for (int i = 0; i < target->para.size(); i++)
	{
		expressionTrans(result, offset, target->para[i]);
		transTo("push", "eax", "");
	}
	//����
	transTo("mov", "eax", "[ebp-8]");
	transTo("push", "eax", "");
	transTo("push", "eip", "");
	transTo("jmp", target->use->headLable, "");
	return;
}

void whileTrans(DefPara, WhileSentence* target)
{
	//��ȡ��ǩ
	string headLable = getWhileLable(true);
	string endLable = getWhileLable(false);
	//����
	transTo(makeLable(headLable), "", "");
	//�����ж�����ת
	expressionTrans(result, offset, target->condition);
	transTo("test", "eax", "FFh");
	transTo("jz", endLable, "");
	//ѭ����
	sentenceTrans(result, offset, target->body);
	//����
	transTo("jmp", headLable, "");
	transTo(makeLable(endLable), "", "");
	transTo("nop", "", "");
	return;
}

void forTrans(DefPara, ForSentence* target)
{
	//��ȡ��ǩ
	string headLable = getForLable(true);
	string endLable = getForLable(false);
	//����
	transTo(makeLable(headLable), "", "");
	//�����ж�����ת
	expressionTrans(result, offset, target->condition);
	transTo("test", "eax", "FFh");
	transTo("jz", endLable, "");
	//ѭ����
	sentenceTrans(result, offset, target->body);
	//ѭ��������
	sentenceTrans(result, offset, target->assign);
	//����
	transTo("jmp", headLable, "");
	transTo(makeLable(endLable), "", "");
	transTo("nop", "", "");
	return;
}

void ifTrans(DefPara, IfSentence* target)
{
	//��ȡ��ǩ
	string elseLable = getIfLable(true);
	string endLable = getIfLable(false);
	//�����жϺ���ת
	expressionTrans(result, offset, target->condition);
	transTo("test", "eax", "FFh");
	transTo("jz", elseLable, "");
	//Ϊ��ʱִ��
	sentenceTrans(result, offset, target->body);
	transTo("jmp", endLable, "");
	//Ϊ��ʱִ��
	transTo(makeLable(elseLable), "", "");
	if (target->hasElse == false)
		transTo("nop", "", "");
	else sentenceTrans(result, offset, target->elseBody);
	//β��
	transTo(makeLable(endLable), "", "");
	transTo("nop", "", "");
	return;
}

void sentenceTrans(DefPara, Sentence* target)
{
	switch (target->type)
	{
		case BLOCK_S:blockTrans(result, offset, (BlockSentence*)target); break;
		case ASSIGN_S:assignTrans(result, offset, (AssignSentence*)target); break;
		case RETURN_S:returnTrans(result, offset, (ReturnSentence*)target); break;
		case CALL_S:callTrans(result, offset, (CallSentence*)target); break;
		case WHILE_S:whileTrans(result, offset, (WhileSentence*)target); break;
		case FOR_S:forTrans(result, offset, (ForSentence*)target); break;
		case IF_S:ifTrans(result, offset, (IfSentence*)target); break;
		case EMPTY_S:transTo("nop","",""); break;
	}
	return;
}

#undef DefPara