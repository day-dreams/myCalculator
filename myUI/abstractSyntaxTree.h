#pragma once
#include"encode.h"
#include<string>
#include<queue>
#include<vector>
#include<unordered_map>

using namespace std;

namespace moon {
	enum nodeType { variable, functor_, base_op, base_fun, value, expression, invalid };

	struct ast_node {
		bool is_func = false;
		vector<string> fun_argv;
		int children_num;
		vector<ast_node> children;
		std::string unit;
	};

	class AbstractSyntaxTree {
	private:
		bool is_functor;
		std::string raw_text;
		ast_node root;
		std::unordered_map<std::string, double> argv;
		std::vector<std::string> _units;
	public:
		/*
		�������ó����﷨��
		*/
		AbstractSyntaxTree();
		AbstractSyntaxTree(std::string text, bool is_functor = true);

		/*
		����������ast��
		*/
		void inorder_ouput();

		/*
		�������
		*/
		void preorder_output();

		/*
		����ΰ���AST��
		*/
		ast_node create_ast_tree(std::vector<std::string>& units,int begin, int end,bool use_func=false);


		/*
			��������һ�׽ӿڣ�����һ����������ϲ�����Ԫ��1,f(2,3)������������ast�����ڵ�
		*/
		ast_node create_ast_tree(std::string unit,bool use_func = false);
		ast_node _create_ast_tree(std::string unit, bool use_func = false);

		/*
			����ast����ֵ�����׽ӿ�
		*/
		double get_value(bool use_func=false);
		double _get_value(ast_node& node,bool usr_func);
		/*
		�жϷ���pos�����Ƿ������ţ�������ʱ����ast��ί�и���һ��
		*/
		bool is_in_bracket(vector<string> &units,int begin, int end, int pos);

		/*
		�����ж�
		*/
		bool is_negtive(vector<string> &units,int pos);

		/*
		�ִʹ���
		*/
		std::vector<std::string>  to_lexical_units(const std::string &text, bool use_func = false);

		nodeType get_unit_type(std::string &text,bool use_func=false);
	};


}

