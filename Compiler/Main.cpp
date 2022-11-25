#include<map>
#include<string>
#include<fstream>
#include<iostream>

#include"debugger.h"
#include"exceptions.h"

#include"match_map.h"
#include"lexic_list.h"
#include"lexical_analyzer.h"

#include"program_struct.h"
#include"gramma_analyzer.h"
using namespace std;

//Debug for gramma_analyzer

int main()
{
	ifstream fin;
	string name = "E:\\��ѧ�γ�\\������_����ԭ��\\ʵ��\\Compiler\\Test.txt";//Test document
	fin.open(name);
	vector<Lexic*> lexicalList = lexicalAnalyzer(fin);

	int pos = 0;
	Program* program = programBuilder(lexicalList, pos);
}
/**/

//Debug for lexical analyzer
/*
int main()
{
	ifstream fin;
	string name="E:\\��ѧ�γ�\\������_����ԭ��\\ʵ��\\Test.txt";//Test document
	fin.open(name);
	vector<Lexic*> res=lexicalAnalyzer(fin);
	for(vector<Lexic*>::iterator it=res.begin();it!=res.end();it++)
	{
		LexicOut(*it);
	}
	fin.close();
	return 0;
}
/**/ 


//Debug for lexical matching
/*
int main()
{
	MatchMap theMap=mapBuild();
	while(1)
	{
		string ori;
		cin>>ori; 
		cout<<"ori_length = "<<ori.length()<<endl;
		Lexic* out=Matching(ori,theMap);
		LexicOut(out);
		delete out;
	}
}
/**/