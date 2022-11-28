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

#include"asm_struct.h"
#include"translater.h"
using namespace std;

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		cout << "未提供有效的参数" << endl;
		return -1;
	}
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);

	try 
	{
		//词法分析
		vector<Lexic*> lexicalList = lexicalAnalyzer(fin);
		//语法分析
		int pos = 0;
		Program* program = programBuilder(lexicalList, pos);
		//翻译成汇编
		vector<ASM> result;
		programTrans(result, 0, program);
		for (int i = 0; i < result.size(); i++)
			fout << result[i].out() << endl;

		cout << "成功" << endl;
	}
	catch (char* e)
	{
		cout << e << endl;
	}

	fin.close();
	fout.close();
	return 0;
}