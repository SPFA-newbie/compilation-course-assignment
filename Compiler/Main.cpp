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



//Debug for lexical analyzer

int main()
{
	ifstream fin;
	string name="E:\\大学课程\\大三上_编译原理\\实验\\Test.txt";//Test document
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