#include<string>
#include<vector>

#include"exceptions.h"
#include"gramma_tool.h"
#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

#define DefPara vector<Lexic*> & target, int & pos

Program* programBuilder(DefPara)
{
	Program* ret=new Program;
	ret->virtualBlock=new BlockSentence;
	ret->virtualBlock->father = NULL;
	while(pos!=target.size())
	{
		if (target[pos]->type == TYPE_DEF)//���庯��
			functionBuilder(target, pos, ret);
		else if (target[pos]->type == CTRL_WORD && (((Control*)target[pos])->word == VAR || ((Control*)target[pos])->word == CONST))//����ֵ
			valueBuilder(target, pos, ret->virtualBlock, ret, true);
		else if (target[pos]->type == SYMBOL && ((SymbolLexic*)target[pos])->symbol == LEFT_BRA)
			ret->main = blockBuilder(target, pos, ret->virtualBlock, ret);
		else throw exceptions::ISOLATED_SYMBOL;
	}
	return ret;
}

void functionBuilder(DefPara, Program* root)
{
	FunctionDefine* fun = new FunctionDefine;
	fun->virtualBlock = new BlockSentence;
	fun->virtualBlock->father = root->virtualBlock;
	//��ȡ��������ֵ����
	fun->returnType = getTypeDefine(target[pos])->valType;
	//��ȡ�������������
	pos++;
	CustomName* funName = getCustomName(target[pos]);
	if (funName == NULL)throw exceptions::ILLEGAL_FUNCTION;
	if (getFunction(funName->name, root) != NULL)throw exceptions::DUPLICATE_FUNCTION;
	fun->tag = getNewNUC();
	//��ȡ������
	pos++;
	if (checkSymbol(target[pos], LEFT_PARE) == false)throw exceptions::ISOLATED_SYMBOL;
	//��ȡ������
	pos++;
	while (checkSymbol(target[pos], RIGHT_PARE) == false)
	{
		//��������
		ValueTypeDefine* paraType = getTypeDefine(target[pos]);
		if (paraType == NULL)throw exceptions::ISOLATED_SYMBOL;
		//��������
		pos++;
		CustomName* paraName = getCustomName(target[pos]);
		if (getValue(paraName->name, fun->virtualBlock) != NULL)throw exceptions::DUPLICATE_VALUE;
		//��������
		ValueDefine* value = createParaValue(false, paraType->valType);
		value->value = NULL;
		fun->virtualBlock->values[paraName->name] = value;
		//�����������
		fun->paraType.push_back(paraType->valType);
		//�������ָ��
		fun->paraList.push_back(value);
		//������
		pos++;
		if (checkSymbol(target[pos], COMMA) == true)pos++; else
		if (checkSymbol(target[pos], RIGHT_PARE) != true)throw exceptions::ISOLATED_SYMBOL;
	}
	//��ȡ�����
	pos++;
	if (checkSymbol(target[pos], LEFT_BRA) == false)throw exceptions::ISOLATED_SYMBOL;
	fun->block = blockBuilder(target, pos, fun->virtualBlock, root);
	//��ӵ�������
	root->functions[funName->name] = fun;
	return;
}

void valueBuilder(DefPara, BlockSentence* father, Program* root, bool isGlobal)
{
	ValueDefine* value = new ValueDefine;
	value->isGlobal = isGlobal;
	//ȷ����������
	if (getControl(target[pos])->word == VAR)value->isConst = false;
		else value->isConst = true;
	//ȷ������
	pos++;
	ValueTypeDefine* type = getTypeDefine(target[pos]);
	if (type == NULL)throw exceptions::MISSING_TYPE_DEFINE;
	value->type = type->valType;
	//ȷ������
	pos++;
	CustomName* name = getCustomName(target[pos]);
	if (name == NULL)throw::exceptions::ILLEGAL_VALUE;
	if (getValue(name->name, father) != NULL)throw exceptions::DUPLICATE_VALUE;
	value->tag = getNewNUC();
	//��ֵ���ż��
	pos++;
	if (checkSymbol(target[pos], ASSIGN) == false)throw exceptions::UNINIT_VALUE;
	//��ȡ��ֵ
	pos++;
	if (target[pos]->type != CONST_VAL)throw exceptions::ILLEGAL_INIT_VALUE;
	value->value = getConstValue(target[pos])->value;
	//�ֺż��
	pos++;
	if (checkSymbol(target[pos], END) == false)throw exceptions::MISSING_SENICOLON;
	pos++;
	//��ӵ�������
	father->values[name->name] = value;
	return;
}

#undef DefType