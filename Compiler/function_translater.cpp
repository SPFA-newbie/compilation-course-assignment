#include<map>
#include<vector>

#include"asm_struct.h"
#include"translater.h"
#include"translate_tool.h"
using namespace std;

void functionTrans(vector<ASM>& result, int offset, FunctionDefine* target)
{
	//确定参数偏移量
	int paraOffset = -4;
	for (int i = target->paraList.size() - 1; i >= 0; i--)
	{
		paraOffset -= 4;
		target->paraList[i]->offset = paraOffset;
	}
	//获取标签
	string headLable = getFunLable(true);
	string endLable = getFunLable(false);
	target->headLable = headLable;
	headLable.append(":");
	endLable.append(":");
	//翻译
	transTo(headLable, "", "");
	transTo("mov", "[ebp-8]", "esp");
	//函数体翻译
	sentenceTrans(result, offset, target->block);
	//翻译
	transTo(endLable, "", "");
	transTo("jmp", "ERROR_TAG","");
	return;
}