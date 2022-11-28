#include<string>

#include"asm_struct.h"
#include"translate_tool.h"
using namespace std;

string offsetMake(string tar, int offset)
{
	string ret = "[";
	ret.append(tar);
	if (offset > 0)
	{
		ret.append("-");
		ret.append(to_string(offset));
	}
	else if (offset < 0)
	{
		ret.append("+");
		ret.append(to_string(-offset));
	}
	ret.append("]");
	return ret;
}

string getFunLable(bool isHead)
{
	string lable = "FUNCTION_";
	if (isHead)
	{
		funUID++;
		lable.append("HEAD");
	}
	else
		lable.append("END");
	lable.append("_");
	lable.append(to_string(funUID));
	return lable;
}
string getCmpLable(bool isTrue)
{
	string lable = "CMP_";
	if (isTrue)
	{
		cmpUID++;
		lable.append("T");
	}
	else
		lable.append("F");
	lable.append("_");
	lable.append(to_string(cmpUID));
	return lable;
}
string getWhileLable(bool isHead)
{
	{
		string lable = "WHILE_";
		if (isHead)
		{
			whileUID++;
			lable.append("HEAD");
		}
		else
			lable.append("END");
		lable.append("_");
		lable.append(to_string(whileUID));
		return lable;
	}
}
string getForLable(bool isHead)
{
	string lable = "FOR_";
	if (isHead)
	{
		forUID++;
		lable.append("HEAD");
	}
	else
		lable.append("END");
	lable.append("_");
	lable.append(to_string(forUID));
	return lable;
}
string getIfLable(bool isElse)
{
	string lable = "";
	if (isElse)
	{
		ifUID++;
		lable.append("ELSE");
	}
	else
		lable.append("IF_END");
	lable.append("_");
	lable.append(to_string(ifUID));
	return lable;
}

string makeLable(string lable)
{
	string ret = lable;
	ret.append(":");
	return ret;
}