#pragma once
#include"encode.h"
#include"abstractSyntaxTree.h"
#include"functor.h"
#include"base.h"
#include<utility>
#include<string>
#include<vector>	
using std::string;
using std::get;
using std::tuple;
using std::vector;
namespace moon {
	
	/*
		解析状态，成功-待显示字符串，失败-出错信息
	*/
	typedef tuple<bool, nodeType,string, string>	parseResult;

	parseResult parse(string input_text);

	/*
		判断输入类型：纯表达式，函数定义，变量定义，
	*/
	nodeType judge_input_type(string &input_text);

	/*
		分词函数
	*/
	vector<string> split(string text, string split_char);

	/*
		括号匹配检测
	*/
	bool check_bracket(std::string& text);

	inline double str_to_double(string& str) {
		auto ite = custom_variable.find(str);
		if (ite != custom_variable.end()) return ite->second;
		else 
			return std::stod(str);
	}

}