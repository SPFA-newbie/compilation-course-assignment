#include<map>
#include<string>
#include<fstream>
#include<iostream>

#include"debugger.h"
#include"match_map.h"
#include"lexic_list.h"
#include"exceptions.h"
#include"lexical_analyzer.h"

using namespace std;

void LexicOut(Lexic* out)
{
	if(out->type==CUS_NAME)cout<<"CUS_NAME\t"<<((CustomName*)out)->name<<endl;else
	if(out->type==TYPE_DEF)cout<<"TYPE_DEF\t"<<((ValueTypeDefine*)out)->valType<<endl;else
	if(out->type==CTRL_WORD)cout<<"CTRL_WORD\t"<<((Control*)out)->word<<endl;else
	if(out->type==SYMBOL)cout<<"SYMBOL\t"<<((SymbolLexic*)out)->symbol<<endl;else
	{
		cout<<"CONST_VAL\t";
		ConstValue* cv=(ConstValue*)out;
		if(cv->valType==CHAR)cout<<"CHAR\t"<<*(char*)(cv->value)<<endl;else
		if(cv->valType==STRING)cout<<"STRING\t"<<*(string*)(cv->value)<<endl;else
		if(cv->valType==SHORT)cout<<"SHORT\t"<<*(short*)(cv->value)<<endl;else
		if(cv->valType==INT)cout<<"INT\t"<<*(int*)(cv->value)<<endl;else
		if(cv->valType==LONG)cout<<"LONG\t"<<*(long long*)(cv->value)<<endl;else
		if(cv->valType==FLOAT)cout<<"FLOAT\t"<<*(float*)(cv->value)<<endl;else
		if(cv->valType==DOUBLE)cout<<"DOUBLE\t"<<*(double*)(cv->value)<<endl;
	}
}