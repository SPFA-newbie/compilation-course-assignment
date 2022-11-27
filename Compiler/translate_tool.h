#pragma once
#ifndef TRANSLATE_TOOL
#define TRANSLATE_TOOL

#include<string>
#include"asm_struct.h"

#define transTo(s1,s2,s3) result.push_back(ASM(s1,s2,s3))

static int funUID = 0;
static int cmpUID = 0;
static int ifUID = 0;
static int whileUID = 0;
static int forUID = 0;

inline std::string valToStr(int* x)
{
	return std::to_string(*x);
}

std::string offsetMake(std::string tar, int offset);

std::string getFunLable(bool isHead);
std::string getCmpLable(bool isTrue);
std::string getWhileLable(bool isHead);
std::string getForLable(bool isHead);
std::string getIfLable(bool isElse);

std::string makeLable(std::string lable);

#endif
