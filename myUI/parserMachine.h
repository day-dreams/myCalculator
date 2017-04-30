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
		����״̬���ɹ�-����ʾ�ַ�����ʧ��-������Ϣ
	*/
	typedef tuple<bool, nodeType,string, string>	parseResult;

	parseResult parse(string input_text);

	/*
		�ж��������ͣ������ʽ���������壬�������壬
	*/
	nodeType judge_input_type(string &input_text);

	/*
		�ִʺ���
	*/
	vector<string> split(string text, string split_char);

	/*
		����ƥ����
	*/
	bool check_bracket(std::string& text);

	inline double str_to_double(string& str) {
		auto ite = custom_variable.find(str);
		if (ite != custom_variable.end()) return ite->second;
		else 
			return std::stod(str);
	}

}