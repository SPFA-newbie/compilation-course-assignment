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
		cout << "δ�ṩ��Ч�Ĳ���" << endl;
		return -1;
	}
	ifstream fin;
	ofstream fout;
	fin.open(argv[1]);
	fout.open(argv[2]);

	try 
	{
		//�ʷ�����
		vector<Lexic*> lexicalList = lexicalAnalyzer(fin);
		//�﷨����
		int pos = 0;
		Program* program = programBuilder(lexicalList, pos);
		//����ɻ��
		vector<ASM> result;
		programTrans(result, 0, program);
		for (int i = 0; i < result.size(); i++)
			fout << result[i].out() << endl;

		cout << "�ɹ�" << endl;
	}
	catch (char* e)
	{
		cout << e << endl;
	}

	fin.close();
	fout.close();
	return 0;
}