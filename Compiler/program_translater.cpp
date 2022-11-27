#include<map>

#include"asm_struct.h"
#include"translater.h"
#include"translate_tool.h"
using namespace std;

void programTrans(vector<ASM>& result, int offset, Program* target)
{
	transTo("push", "ebp", "");
	transTo("mov", "ebp", "esp");
	transTo("push", "FFFFFFFFh", "");
	transTo("push", "FFFFFFFFh", "");

	offset = 8;

	//翻译全局变量定义
	map<string, ValueDefine*>::iterator vit = target->virtualBlock->values.begin();
	for (; vit != target->virtualBlock->values.end(); vit++)
	{
		offset += 4;
		vit->second->offset = offset;
		transTo("mov", "eax", valToStr((int*)vit->second->value));
		transTo("push", "eax","");
	}
	
	transTo("jmp", "MAIN","");

	//翻译函数定义
	map<string, FunctionDefine*>::iterator fit = target->functions.begin();
	for (; fit!=target->functions.end(); fit++)
		functionTrans(result, 0, fit->second);
	
	transTo("MAIN:", "", "");
	transTo("mov", "[ebp-8]", "esp");

	//翻译主函数
	sentenceTrans(result, 0, target->main);

	transTo("jmp", "PROGRAM_END","");
	transTo("ERROR_TAG:", "", "");
	transTo("nop","","");
	transTo("PROGRAM_END:","","");
	transTo("pop", "eax", "");
	transTo("pop", "eax", "");
	transTo("pop", "ebp", "");
}