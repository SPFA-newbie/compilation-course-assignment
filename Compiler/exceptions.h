#pragma once
#ifndef EXCEPTIONS
#define EXCEPTIONS

namespace exceptions
{
	//�ʷ�����
	static const char* ILLEGAL_CONST = "�Ƿ�����";
	static const char* ILLEGAL_SYMBOL = "�Ƿ�����";
	//�﷨����
	//-- ͨ��
	static const char* ISOLATED_SYMBOL = "�����ķ���";
	static const char* MISSING_SENICOLON = "ȱ�ٷֺ�";
	static const char* UNCLOSED_BRACKET = "����δ���";
	//-- �����������
	static const char* ILLEGAL_FUNCTION = "�Ƿ��ĺ�����";
	static const char* ILLEGAL_VALUE = "�Ƿ��ı�����";
	static const char* UNDEFINED_FUNCTION = "δ����ĺ���";
	static const char* UNDEFINED_VALUE = "δ����ĳ���/����";
	static const char* DUPLICATE_FUNCTION = "�ض���ĺ�����";
	static const char* DUPLICATE_VALUE = "�ض���ĳ���/������";
	static const char* UNINIT_VALUE = "δ��ʼ���ĳ���/����";
	//-- ��ֵ
	static const char* CHANGE_CONST = "�ı䳣����ֵ";
	//-- while��if���
	static const char* MISSING_CONDITION = "ȱ����������������������";
	static const char* MISSING_THEN = "ȱ��then�ؼ���";
	//-- for���
	static const char* MISSING_COUNTER = "ȱ�ټ���������������";
	//-- ��������
	static const char* TOO_MANY_PARAMENT = "��������";
	static const char* MISSING_PARAMENT = "ȱ�ٲ���";
}

#endif