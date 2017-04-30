#pragma once
#include"encode.h"
#include<string>
#include<exception>

using std::exception;
using std::string;

namespace moon {

	class unkown_signal :public exception {
	public:
		unkown_signal() :exception("�Ƿ����룺����δ����ķ���") {}
	};


	class unkown_op :public exception {
	public:
		unkown_op() :exception("�Ƿ����룺����δ������������") {}
	};

	class too_much_eval :public exception {
	public:
		too_much_eval() :exception("�Ƿ����룺 ����ʱ����̫����š�=��") {}
	};

	class too_much_left_bracket :public exception {
	public:
		too_much_left_bracket() :exception("�Ƿ����룺 ���庯��ʱ����̫����š�(��") {}
	};

	class too_much_right_bracket :public exception {
	public:
		too_much_right_bracket() :exception("�Ƿ����룺 ���庯��ʱ����̫����š�)��") {}
	};

	class va_before_va :public exception {
	public:
		va_before_va(string info) :exception((string("�Ƿ����룺������ȱ�������\t")+info).c_str()) {}
	};

	class log_negtive :public exception {

	public:
		log_negtive() :exception("�Ƿ����㣺���ܶԸ���ȡ������") {}
	};

	class division_zero :public exception {
	public:
		division_zero() :exception("�Ƿ����㣺0������Ϊ������") {}
	};

	class arc_range :public exception {
	public:
		arc_range() :exception("�Ƿ����㣺�����Ǻ�����������ֵ���ܳ���1��") {}
	};


	class lack_of_num :public exception {
	public:
		lack_of_num():exception("�Ƿ����㣺��Ԫ�����ȱ�ٲ�����"){}
	};
}