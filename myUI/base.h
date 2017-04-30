#pragma once
#include"encode.h"
#include"abstractSyntaxTree.h"
#include"functor.h"
#include"baseException.h"
#include<string>
#include<map>

namespace moon {
	extern std::map<std::string, int> base_op_priority;
	extern std::map<std::string, int> base_op_argc; 
	extern std::map<std::string, int> base_fun_priority;
	extern std::map<std::string, moon::my_functor> custom_function;
	extern std::map<std::string, double> custom_variable;
	int get_base_op_argc(std::string& markup);//获取基本运算符运算目数
	int get_base_op_priority(std::string& markup);//获取基本运算符优先级


}
