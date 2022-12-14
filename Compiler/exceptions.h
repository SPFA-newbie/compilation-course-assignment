#pragma once
#ifndef EXCEPTIONS
#define EXCEPTIONS

namespace exceptions
{
	//词法分析
	static const char* ILLEGAL_CONST = "非法常量";
	static const char* ILLEGAL_SYMBOL = "非法符号";
	//语法分析
	//-- 通用
	static const char* ISOLATED_SYMBOL = "孤立的符号";
	static const char* MISSING_SENICOLON = "缺少分号";
	static const char* UNCLOSED_BRACKET = "括号未封闭";
	//-- 函数与变量名
	static const char* ILLEGAL_FUNCTION = "非法的函数名";
	static const char* ILLEGAL_VALUE = "非法的变量名";
	static const char* UNDEFINED_FUNCTION = "未定义的函数";
	static const char* UNDEFINED_VALUE = "未定义的常量/变量";
	static const char* DUPLICATE_FUNCTION = "重定义的函数名";
	static const char* DUPLICATE_VALUE = "重定义的常量/变量名";
	static const char* UNINIT_VALUE = "未初始化的常量/变量";
	//-- 常量变量定义
	static const char* MISSING_TYPE_DEFINE = "缺少类型定义";
	static const char* ILLEGAL_INIT_VALUE = "非法的初始值或缺少初始值";
	//-- 赋值
	static const char* CHANGE_CONST = "改变常量的值";
	//-- while和if语句
	static const char* MISSING_CONDITION = "缺少条件或条件不在括号中";
	static const char* MISSING_THEN = "缺少then关键字";
	//-- for语句
	static const char* MISSING_COUNTER = "缺少计数器或不在括号中";
	//-- 函数调用
	static const char* TOO_MANY_PARAMENT = "参数过多";
	static const char* MISSING_PARAMENT = "缺少参数";
	//-- 表达式
	static const char* ILLEGAL_EXPRESSION_ELEMENT = "非法的(子)表达式元素";
	static const char* ILLEGAL_OR_MISSING_OPERATOR = "非法的运算符或缺少运算符";
	static const char* MISSING_BRACKET = "表达式缺少必要的括号";
	static const char* EXPRESSION_UNNORMALIZED = "表达式构造失败：无法规范化";
}

#endif