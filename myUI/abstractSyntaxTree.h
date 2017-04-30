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
		构建整棵抽象语法树
		*/
		AbstractSyntaxTree();
		AbstractSyntaxTree(std::string text, bool is_functor = true);

		/*
		中序遍历输出ast树
		*/
		void inorder_ouput();

		/*
		先序遍历
		*/
		void preorder_output();

		/*
		创建伟大的AST树
		*/
		ast_node create_ast_tree(std::vector<std::string>& units,int begin, int end,bool use_func=false);


		/*
			建树，另一套接口：接受一个函数的组合参数单元（1,f(2,3)），返回它的ast树根节点
		*/
		ast_node create_ast_tree(std::string unit,bool use_func = false);
		ast_node _create_ast_tree(std::string unit, bool use_func = false);

		/*
			计算ast树的值，两套接口
		*/
		double get_value(bool use_func=false);
		double _get_value(ast_node& node,bool usr_func);
		/*
		判断符号pos两边是否有括号，有则暂时生成ast，委托给下一级
		*/
		bool is_in_bracket(vector<string> &units,int begin, int end, int pos);

		/*
		负号判断
		*/
		bool is_negtive(vector<string> &units,int pos);

		/*
		分词功能
		*/
		std::vector<std::string>  to_lexical_units(const std::string &text, bool use_func = false);

		nodeType get_unit_type(std::string &text,bool use_func=false);
	};


}

