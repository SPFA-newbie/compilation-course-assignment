#include<map>
#include<vector>

#include"asm_struct.h"
#include"translater.h"
#include"translate_tool.h"
using namespace std;

void functionTrans(vector<ASM>& result, int offset, FunctionDefine* target)
{
	//ȷ������ƫ����
	int paraOffset = -4;
	for (int i = target->paraList.size() - 1; i >= 0; i--)
	{
		paraOffset -= 4;
		target->paraList[i]->offset = paraOffset;
	}
	//��ȡ��ǩ
	string headLable = getFunLable(true);
	string endLable = getFunLable(false);
	target->headLable = headLable;
	headLable.append(":");
	endLable.append(":");
	//����
	transTo(headLable, "", "");
	transTo("mov", "[ebp-8]", "esp");
	//�����巭��
	sentenceTrans(result, offset, target->block);
	//����
	transTo(endLable, "", "");
	transTo("jmp", "ERROR_TAG","");
	return;
}