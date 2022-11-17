#include<string>
#include<vector>
#include<fstream>

#include"match_map.h"
#include"lexic_list.h"
#include"exceptions.h"
#include"lexical_analyzer.h"

using namespace std;

vector<Lexic*> lexicalAnalyzer(ifstream& fin)
{
	MatchMap maps=mapBuild();
	vector<Lexic*> ret;
	string lexic="";
	string symbolChar=",;/*-+=%$&!|^()[]{}<>";
	string singleSymbol="/*-+$^{}[](),;";
	string comSymbol="&& || == != <= >=";
	string stopChar="\n \t";
	bool inComSymbol=false;
	bool inStr=false;
	bool inChar=false; 
	char in=fin.get();
	
	while(!fin.eof())
	{
		if(in=='\"')//双引号处理 
		{
			if(inStr)//结束引号 
			{
				lexic.push_back(in);
				ret.push_back(Matching(lexic,maps));
				lexic.clear();
			}else//开始引号
			{
				if(lexic.length()!=0)
				{
					ret.push_back(Matching(lexic,maps));
					lexic.clear();
				}
				lexic.push_back(in);
			}
			inStr=(!inStr);
		}else if(in=='\'')//单引号处理
		{
		 	if(inChar)//结束引号 
			{
				lexic.push_back(in);
				ret.push_back(Matching(lexic,maps));
				lexic.clear();
			}else//开始引号
			{
				if(lexic.length()!=0)
				{
					ret.push_back(Matching(lexic,maps));
					lexic.clear();
				}
				lexic.push_back(in);
			}
			inChar=(!inChar);
		}else if(inStr || inChar)//字符（串）处理
		{
			lexic.push_back(in); 
			if(in=='\\')//转义处理
			{
				in=fin.get();
				lexic.push_back(in);
			} 
		}else if(stopChar.find(in)!=-1)//无意义符号
		{
			if(lexic.length()!=0)
			{
				ret.push_back(Matching(lexic,maps));
				lexic.clear();
			}
			inComSymbol=false;
		}else if(singleSymbol.find(in)!=-1)//独立符号
		{
			if(lexic.length()!=0)
			{
				ret.push_back(Matching(lexic,maps));
				lexic.clear();
			}
			lexic.push_back(in);
			ret.push_back(Matching(lexic,maps));
			lexic.clear();
			inComSymbol=false;
			if(in=='\"')inStr=(!inStr);
			if(in=='\'')inChar=(!inChar);
		}else if(symbolChar.find(in)!=-1)//可能是复合符号
		{
			if(inComSymbol)//已经有一个开头的符号 
			{
				lexic.push_back(in);
				if(comSymbol.find(lexic)!=-1)//确实是复合符号 
				{
					ret.push_back(Matching(lexic,maps));
					lexic.clear();
					inComSymbol=false; 
				}else//不是复合符号
				{
					ret.push_back(Matching(lexic.substr(0,lexic.length()-1),maps));
					lexic.clear();
					lexic.push_back(in);
					inComSymbol=true;
				}
			}else//可能是开头符号
			{
				if(lexic.length()!=0)
				{
					ret.push_back(Matching(lexic,maps));
					lexic.clear();
				}
				lexic.push_back(in);
				inComSymbol=true;
			}
		}else//其他情况 
		{
			if(inComSymbol)//上一个词法单元是符号
			{
				ret.push_back(Matching(lexic,maps));
				lexic.clear();
			}
			lexic.push_back(in);
			inComSymbol=false;
		}
		in=fin.get();
	}
	if(lexic.length()!=0)
	 ret.push_back(Matching(lexic,maps));
	return ret;
}
