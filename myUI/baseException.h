#pragma once
#include"encode.h"
#include<string>
#include<exception>

using std::exception;
using std::string;

namespace moon {

	class unkown_signal :public exception {
	public:
		unkown_signal() :exception("非法输入：出现未定义的符号") {}
	};


	class unkown_op :public exception {
	public:
		unkown_op() :exception("非法输入：出现未定义的运算符号") {}
	};

	class too_much_eval :public exception {
	public:
		too_much_eval() :exception("非法输入： 定义时出现太多符号‘=’") {}
	};

	class too_much_left_bracket :public exception {
	public:
		too_much_left_bracket() :exception("非法输入： 定义函数时出现太多符号‘(’") {}
	};

	class too_much_right_bracket :public exception {
	public:
		too_much_right_bracket() :exception("非法输入： 定义函数时出现太多符号‘)’") {}
	};

	class va_before_va :public exception {
	public:
		va_before_va(string info) :exception((string("非法输入：变量间缺少运算符\t")+info).c_str()) {}
	};

	class log_negtive :public exception {

	public:
		log_negtive() :exception("非法运算：不能对负数取对数！") {}
	};

	class division_zero :public exception {
	public:
		division_zero() :exception("非法运算：0不能作为除数！") {}
	};

	class arc_range :public exception {
	public:
		arc_range() :exception("非法运算：反三角函数参数绝对值不能超过1！") {}
	};


	class lack_of_num :public exception {
	public:
		lack_of_num():exception("非法运算：二元运算符缺少操作数"){}
	};
}