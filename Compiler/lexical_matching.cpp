#include<string>
#include<map>

#include "match_map.h"
#include "lexic_list.h"
#include "exceptions.h"

using namespace std;

char takeEscape(char ch)
{
	char ret;
	if(ch=='0')ret='\0';else
	if(ch=='t')ret='\t';else
	if(ch=='n')ret='\n';else
	if(ch=='\"')ret='\"';else
	if(ch=='\'')ret='\'';else
	if(ch=='\\')ret='\\';else
	 throw exceptions::ILLEGAL_CONST;
	return ret;
} 

string stringMaker(string ori)
{
	int pos=1;
	string ret="";
	while(pos<ori.length() && ori[pos]!='\"')
	{
		if(ori[pos]=='\\')
		{
			pos++;
			ret.push_back(takeEscape(ori[pos]));
		}else ret.push_back(ori[pos]);
		pos++;
	}
	if(pos==ori.length())throw exceptions::ILLEGAL_CONST;
	return ret;
}
short shortMaker(string ori)
{
	short val=0;
	int pos=0;
	while(ori[pos]!='s')
	{
		val*=10;						
		if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
		{
			val+=(ori[pos]-'0');
		}else throw  exceptions::ILLEGAL_CONST;
		pos++;
	}
	if(pos+1!=ori.length())throw exceptions::ILLEGAL_CONST;
	return val;
}
int intMaker(string ori)
{
	int val=0;
	int pos=0;
	while(pos<ori.length())
	{
		val*=10;						
		if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
		{
			val+=(ori[pos]-'0');
		}else throw  exceptions::ILLEGAL_CONST;
		pos++;
	}
	if(pos!=ori.length())throw exceptions::ILLEGAL_CONST;
	return val;	
}
long long longMaker(string ori)
{
	long long val=0;
	int pos=0;
	while(ori[pos]!='l')
	{
		val*=10;						
		if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
		{
			val+=(ori[pos]-'0');
		}else throw  exceptions::ILLEGAL_CONST;
		pos++;
	}
	if(pos+1!=ori.length())throw exceptions::ILLEGAL_CONST;
	return val;	
}
float floatMaker(string ori)
{
	float val=0;
	int pos=0;
	while(ori[pos]!='.' && ori[pos]!='f')
	{
		val*=10;						
		if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
		{
			val+=(ori[pos]-'0');
		}else throw  exceptions::ILLEGAL_CONST;
		pos++;
	}
	if(ori[pos]=='.')
	{
		pos++;
		float level=1; 
		while(ori[pos]!='f')
		{ 
			level*=10;						
			if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
			{
				val+=((ori[pos]-'0')/level);
			}else throw  exceptions::ILLEGAL_CONST;
			pos++;
		}
	}
	if(pos+1!=ori.length())throw exceptions::ILLEGAL_CONST;
	return val;
}
double doubleMaker(string ori)
{
	double val=0;
	int pos=0;
	while(ori[pos]!='.' && pos<ori.length())
	{
		val*=10;						
		if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
		{
			val+=(ori[pos]-'0');
		}else throw  exceptions::ILLEGAL_CONST;
		pos++;
	}
	if(ori[pos]=='.')
	{
		pos++;
		double level=1; 
		while(pos<ori.length())
		{ 
			level*=10;				
			if(ori[pos]-'0'<=9 && ori[pos]-'0'>=0)
			{
				val+=((ori[pos]-'0')/level);
			}else throw  exceptions::ILLEGAL_CONST;
			pos++;
		}
	}
	if(pos!=ori.length())throw exceptions::ILLEGAL_CONST;
	return val;
}

Lexic* Matching(string ori, MatchMap& maps)
{
	Lexic* ret=NULL;
	if(maps.typeMap.find(ori)!=maps.typeMap.end())
	{
		LexicType type=maps.typeMap[ori];
		if(type==TYPE_DEF)
		{
			ValueTypeDefine* want=new ValueTypeDefine;
			want->type=type;
			want->valType=maps.valTypeMap[ori];
			ret=want;
		}else if(type==CTRL_WORD)
		{
			Control* want=new Control;
			want->type=type;
			want->word=maps.ctrlMap[ori];
			ret=want;
		}else if(type==SYMBOL)
		{
			SymbolLexic* want=new SymbolLexic;
			want->type=type;
			want->symbol=maps.symbolMap[ori];
			ret=want;
		}
	}else if((ori[0]>='0'&&ori[0]<='9')||ori[0]=='-'||ori[0]=='\''||ori[0]=='\"')//常量处理 
	{
		ConstValue* want=new ConstValue;
		want->type=CONST_VAL;
		if(ori[0]=='\'')//字符
		{
			want->valType=CHAR;
			want->value=new char; 
			if(ori[1]=='\\')
			{
				*(char*)(want->value)=takeEscape(ori[2]);
				if(ori.length()!=4)throw exceptions::ILLEGAL_CONST;
			}else
			{
				*(char*)(want->value)=ori[1];
				if(ori.length()!=3)throw exceptions::ILLEGAL_CONST;
			}
		}else if(ori[0]=='\"')//字符串 
		{
			want->valType=STRING;
			want->value=new string;
			*(string*)(want->value)=stringMaker(ori);
		}else if(ori[0]>='0'&&ori[0]<='9')//数字 
		{
			if(ori.find('.')==-1 && ori.find('f')==-1)//整数
			{
				if(ori.find('s')!=-1)//短整数
				{
					want->valType=SHORT;
					want->value=new short;
					*(short*)(want->value)=shortMaker(ori);
				}else if(ori.find('l')!=-1)//长整数 
				{
					want->valType=LONG;
					want->value=new long long;
					*(long long*)(want->value)=longMaker(ori);
				}else//整数 
				{
					want->valType=INT;
					want->value=new int;
					*(int*)(want->value)=intMaker(ori);
				}
			}else//浮点数 
			{
				if(ori.find('f')!=-1)//浮点数 
				{
					want->valType=FLOAT;
					want->value=new float;
					*(float*)(want->value)=floatMaker(ori);
				}else if(ori.find('.')!=-1)//双浮点数 
				{
					want->valType=DOUBLE;
					want->value=new double;
					*(double*)(want->value)=doubleMaker(ori);
				}
			}
		}
		ret=want;
	}else if((ori[0]>='a' && ori[0]<='z') || (ori[0]>='A' && ori[0]<='Z') || ori[0]=='_')//自定义函名 
	{
		CustomName* want=new CustomName;
		want->type=CUS_NAME;
		want->name=ori;
		ret=want; 
	}else throw exceptions::ILLEGAL_SYMBOL;
	return ret; 
}