#pragma once
#ifndef MATCH_MAP
#define MATCH_MAP

#include<map>
#include<string>
#include"lexic_list.h" 
class MatchMap
{
	public:
		std::map<std::string, LexicType> typeMap;
		
		std::map<std::string, ValueType> valTypeMap;
		std::map<std::string, CtrlWord> ctrlMap;
		std::map<std::string, Symbol> symbolMap;
};

MatchMap mapBuild();
Lexic* Matching(std::string ori, MatchMap& maps);

#endif