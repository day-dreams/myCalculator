#include"parserMachine.h"
#include"encode.h"
#include"base.h"
#include"abstractSyntaxTree.h"
#include"functor.h"
#include"baseException.h"
#include<utility>
#include<string>
#include<exception>
#include<algorithm>

using std::string;
using std::get;
using std::tuple;

namespace moon {
	
	nodeType judge_input_type(string &input_text) {
		using namespace std;
		vector<string> split_result = split(input_text, "=");
		if (split_result.size() > 2) throw too_much_eval();
		if (split_result.size() == 1) {// �����ʽ
			return nodeType::expression;
		}
		else if (split_result.size() == 2) {//�������������
			auto ite=split_result[0].find('(');
			if (ite == string::npos) {//����
				return nodeType::variable;
			}
			else {//����
				return nodeType::functor_;
			}			
		}
	}
	
	parseResult parse(string input_text) {
		using namespace std;
		parseResult result;
		if (!check_bracket(input_text)) {
			get<0>(result) = false;
			get<3>(result) = "����������Ų�ƥ��";
			return result;
		}
		auto type = judge_input_type(input_text);
		try {
			if (type == nodeType::expression) {//���ʽ��ֵ
				AbstractSyntaxTree ast(input_text);
				get<0>(result) = true;
				get<2>(result) = to_string(ast.get_value(true));
			}
			else if (type == nodeType::functor_) {//���庯��
				my_functor new_fun(input_text);
				get<0>(result) = true;
				get<2>(result) = string("��������ɹ�")+new_fun.markup;
				custom_function[new_fun.markup] = move(new_fun);
			}
			else if (type == nodeType::variable) {//�������
				auto pos = input_text.find("=");
				custom_variable[input_text.substr(0, pos)] = str_to_double(input_text.substr(pos+1));
				get<0>(result) = true;
				get<2>(result) = input_text.substr(0, pos)+string("=") + to_string(custom_variable[input_text.substr(0, pos)]);
			}
		}
		catch (std::exception& e) {//�Ƿ�����
			get<0>(result) = false;
			get<3>(result) = e.what();
		}
		get<1>(result) = type;
		return result;
	}

	vector<string> split(string text, string split_char) {
		vector<string> result;
		for (string::size_type pos_begin = 0; true;) {
			auto pos_end = text.find(split_char, pos_begin + 1);
			result.push_back(text.substr(pos_begin, pos_end - pos_begin));
			if (pos_end == string::npos) break;
			else pos_begin = pos_end + 1;
		}
		return std::move(result);
	}


	bool check_bracket(std::string& text) {
		int num = 0;
		for (auto &x : text) {
			if (x== '(') ++num;
			else if (x == ')') --num;
			if (num < 0) return false;
		}
		if (num != 0) return false;
		return true;
	}

}