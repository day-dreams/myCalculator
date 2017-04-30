#pragma once
#define _USE_MATH_DEFINES
#include"base.h"
#include<string>

namespace moon {
	std::map<std::string, int> base_op_priority = {
		{ ",",0 },
		{ "+", 1 },{ "-", 1 },
		{ "*", 2 },{ "/", 2 },
		{ "^",4 },
		{ "(", 5 },{ ")", 5 }
	};
	std::map<std::string, int> base_fun_priority = {
		{ "log",3 },{ "ln",3 },{ "lg",3 },{ "sin",3 },{ "cos",3 },{ "tan",3 },{ "arcsin",3 },{ "arccos",3 },{ "arctan",3 },
	};
	std::map<std::string, int> base_op_argc= {
		{ ",",0 },
		{ "+", 2 },{ "-", 2 },{ "*", 2 },{ "/", 2 },{ "^",2 },
		{ "log",1 },{ "ln",1 },{ "lg",1 },{ "sin",1 },{ "cos",1 },{ "tan",1 },{ "arcsin",1 },{ "arccos",1 },{ "arctan",1 },
		{ "(", 1 },{ ")", 1 }
	};
	std::map<std::string, moon::my_functor> custom_function = { 
		{"f",moon::my_functor()} 
	};
	std::map<std::string, double> custom_variable = {
		{"PI",M_PI},
		{"E",exp(1)}
	};

	int get_base_op_priority(std::string& markup) {
		auto ite= base_op_priority.find(markup);
		if (ite == base_op_priority.end()) return-1;
		else return ite->second;
	}
	int get_base_op_argc(std::string& markup) {
		auto ite = base_op_argc.find(markup);
		if (ite == base_op_argc.end()) return -1;
		else return ite->second;
	}
}