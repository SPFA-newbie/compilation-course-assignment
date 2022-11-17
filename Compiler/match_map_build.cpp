#include<map>
#include<string>
#include"match_map.h"
#include"lexic_list.h"
using namespace std;

MatchMap mapBuild()
{
	MatchMap ret;
	map<string, LexicType> typeMap;		
	map<string, ValueType> valTypeMap;
	map<string, CtrlWord> ctrlMap;
	map<string, Symbol> symbolMap;
	
	typeMap["short"]=typeMap["int"]=typeMap["long"]=
	typeMap["float"]=typeMap["double"]=typeMap["char"]=
	typeMap["string"]=typeMap["void"]=TYPE_DEF;
	valTypeMap["short"]=SHORT;valTypeMap["int"]=INT;valTypeMap["long"]=LONG;
	valTypeMap["float"]=FLOAT;valTypeMap["double"]=DOUBLE;valTypeMap["char"]=CHAR; 
	valTypeMap["string"]=STRING;valTypeMap["void"]=VOID;
	
	typeMap["if"]=typeMap["then"]=typeMap["else"]=
	typeMap["while"]=typeMap["for"]=typeMap["continue"]=
	typeMap["break"]=typeMap["const"]=typeMap["return"]=
	typeMap["var"]=CTRL_WORD;
	ctrlMap["if"]=IF;ctrlMap["then"]=THEN;ctrlMap["else"]=ELSE;
	ctrlMap["while"]=WHILE;ctrlMap["for"]=FOR;ctrlMap["continue"]=CONTINUE;
	ctrlMap["break"]=BREAK;ctrlMap["const"]=CONST;ctrlMap["return"]=RETURN;
	ctrlMap["var"]=VAR;
	
	typeMap["&"]=typeMap["|"]=typeMap["!"]=typeMap["^"]=typeMap["+"]=typeMap["-"]=
	typeMap["*"]=typeMap["/"]=typeMap["%"]=typeMap["$"]=typeMap["&&"]=typeMap["||"]=
	typeMap["<"]=typeMap[">"]=typeMap["=="]=typeMap["!="]=typeMap[">="]=typeMap["<="]=
	typeMap["="]=typeMap["{"]=typeMap["}"]=typeMap["["]=typeMap["]"]=typeMap["("]=
	typeMap[")"]=typeMap[";"]=typeMap[","]=SYMBOL;
	symbolMap["&"]=AND;symbolMap["|"]=OR;symbolMap["!"]=NOT;symbolMap["^"]=XOR;
	symbolMap["+"]=ADD;symbolMap["-"]=SUB;symbolMap["*"]=MUL;symbolMap["/"]=DIV;
	symbolMap["%"]=MOD;symbolMap["$"]=NEG;symbolMap["&&"]=LOG_AND;symbolMap["||"]=LOG_OR;
	symbolMap["<"]=LT;symbolMap[">"]=GT;symbolMap["=="]=EQ;symbolMap["!="]=NE;
	symbolMap[">="]=GE;symbolMap["<="]=LE;symbolMap["="]=ASSIGN;symbolMap["{"]=LEFT_BRA;
	symbolMap["}"]=RIGHT_BRA;symbolMap["["]=LEFT_SQU;symbolMap["]"]=RIGHT_SQU;symbolMap["("]=LEFT_PARE;
	symbolMap[")"]=RIGHT_PARE;symbolMap[";"]=END;symbolMap[","]=COMMA;
	
	ret.typeMap=typeMap;
	ret.valTypeMap=valTypeMap;
	ret.ctrlMap=ctrlMap;
	ret.symbolMap=symbolMap;
	return ret;
}