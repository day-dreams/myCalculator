#define _USE_MATH_DEFINES

#include"abstractSyntaxTree.h"
#include"parserMachine.h"
#include"base.h"
#include<cmath>
#include<queue>
#include<string>
#include<vector>
#include<regex>
#include<iostream>


moon::AbstractSyntaxTree::AbstractSyntaxTree()
{
}

moon::AbstractSyntaxTree::AbstractSyntaxTree(std::string text, bool is_functor):raw_text(text)
{
	if (is_functor) {
		if (text.find("=") != string::npos) {
			auto argv_name = split(text.substr(text.find("(") + 1, text.find("=") - 2 - text.find("(")), " ");
			for (auto &name : argv_name)
				argv[name] = 0;
			text = text.substr(text.find("=") + 1);
		}
	}
	_units=to_lexical_units(text, is_functor);
	root = create_ast_tree(_units,0, _units.size(), is_functor);
}
void _inorder_ouput(moon:: ast_node& root)
{
	if (root.is_func) {
		cout << root.unit;
		cout << "(";
		for (auto &x : root.children)
			_inorder_ouput(x);
		cout << ") ";
		return;
	}
	if (root.children_num == 0) cout << root.unit << " ";
	else if (root.children_num == 1) {
		cout << root.unit << " ";
		_inorder_ouput(root.children.front());
	}
	else {
		_inorder_ouput(root.children.front());
		cout << root.unit << " ";
		_inorder_ouput(root.children.back());
	}
}

void moon::AbstractSyntaxTree::inorder_ouput()
{
	_inorder_ouput(root);
	cout << endl;
}

void _preorder_output(moon::ast_node &root) {
	if (root.is_func) {
		cout << root.unit;
		cout << "(";
		for (auto &x : root.children)
			_preorder_output(x);
		cout << ") ";
		return;
	}
	if (root.children_num == 0) cout << root.unit << " ";
	else if (root.children_num == 1) {
		cout << root.unit << " ";
		_inorder_ouput(root.children.front());
	}
	else {
		cout << root.unit << " ";
		_inorder_ouput(root.children.front());
		_inorder_ouput(root.children.back());
	}
}

void moon::AbstractSyntaxTree::preorder_output()
{
	_preorder_output(root);
	cout<<endl;
}

moon::ast_node moon::AbstractSyntaxTree::create_ast_tree(vector<string>& units,int begin, int end, bool use_func)
{
			using namespace std;
			if (units[begin] == "(" && units[end - 1] == ")") {
				int bracket_num = 0;
				for (int i = begin; i != end; ++i)
				{
					if (units[i] == "(") ++bracket_num;
					else if (units[i] == ")") --bracket_num;
					if (bracket_num == 0) {
						if (i != end - 1) {
							//完成
							break;
						}
						else {
							--end;
							++begin;
							break;
						}
					}
				}
			}
			ast_node node;
			/*缺少操作数*/
			if (begin == end)
			{
				throw lack_of_num();
			}
			/*zeore level: variable or value*/
			if (begin + 1 == end&&units[begin].find(",")==string::npos) {
				node.children_num = 0;
				node.unit = units[begin];
				return move(node);
			}
			/*first level:+ - */
			for (int i = end - 1; i >= begin; --i) {
				auto flag = is_in_bracket(units,begin, end, i);
				if (units[i] == "+" && !flag) {
					node.unit = "+";
					node.children_num = 2;
					node.children.push_back(create_ast_tree(units,begin, i,use_func));
					node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
					return move(node);
				}
				else if (units[i] == "-" && !flag &&!is_negtive(units,i)) {
					node.unit = "-";
					node.children_num = 2;
					node.children.push_back(create_ast_tree(units,begin, i,use_func));
					node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
					return move(node);
				}
			}
			/*second level:* / */
			for (int i = end-1; i != begin; --i) {
				auto flag = is_in_bracket(units,begin, end, i);
				if (units[i] == "*" && !flag) {
					node.unit = "*";
					node.children_num = 2;
					node.children.push_back(create_ast_tree(units,begin, i,use_func));
					node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
					return move(node);
				}
				else if (units[i] == "/"&&!flag) {
					node.unit = "/";
					node.children_num = 2;
					node.children.push_back(create_ast_tree(units,begin, i,use_func));
					node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
					return move(node);
				}
			}
			/*third level: ^ */
			for (int i = end - 1; i >= begin; --i) {
				if (units[i] == "^"&&!is_in_bracket(units,begin, end, i)) {
					node.unit = "^";
					node.children_num = 2;
					node.children.push_back(create_ast_tree(units,begin, i,use_func));
					node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
					return node;
				}
			}
			/*foutrh level: - */
			for (int i = end - 1; i >= begin; --i) {
				if (units[i] == "-"&&is_negtive(units,i) && !is_in_bracket(units,begin, end, i)) {
					//if(get_unit_type(units[i-1],true)==-)
					node.unit = "-";
					node.children_num = 1;
					node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
					return node;
				}
			}
			/*fivth level: 各种函数 需要创建函数节点，即设置node.is_functor=true*/
			for (int i = end - 1; i >= begin; --i) {
				if (!is_in_bracket(units,begin, end, i)) {
					auto type = get_unit_type(units[i],use_func);
					if (type == nodeType::base_fun) {
						node.is_func = true;
						node.unit = units[i];
						node.children_num = 1;
						node.children.push_back(create_ast_tree(units,i + 1, end,use_func));
						return node;
					}
					else if (type == nodeType::functor_) {
						node.is_func = true;
						node.unit = units[i];
						string in_bracket;
						int bracket_num = 1;
						for (int index = i +2; index < end; ++index) {
							if (units[index] == "(") ++bracket_num;
							else if (units[index] == ")") --bracket_num;
							in_bracket.append(units[index]);
						}
						in_bracket.pop_back();
						vector<string> tem_argv;
						if (in_bracket.find(",") == string::npos)
							tem_argv.push_back(in_bracket);
						else 
							for (int i = 0; i < in_bracket.size();++i)
								if (in_bracket[i] == ',') {
									tem_argv.push_back(in_bracket.substr(0, i));
									tem_argv.push_back(in_bracket.substr(i + 1));
									break;
								}
							for (auto &x : tem_argv)
								node.children.push_back(create_ast_tree(x,true));
							node.children_num = node.children.size();
							return node;
						}
					else if (type == expression) {
						return create_ast_tree(units[i], true);
					}
				}
				}
			/*sixth level: 括号包裹的子式*/
			auto x = create_ast_tree(units,begin, end,use_func);
			return move(x);
		}


moon::ast_node moon::AbstractSyntaxTree::create_ast_tree(std::string unit, bool use_func)
{
	auto type = get_unit_type(unit,use_func);
	if (type == nodeType::value || type == nodeType::variable) {
		ast_node node;
		node.unit = unit;
		node.children_num = 0;
		return node;
	}
	else {
		return _create_ast_tree(unit, use_func);
	}
	return ast_node();
}

moon::ast_node moon::AbstractSyntaxTree::_create_ast_tree(std::string unit, bool use_func)
{
	using namespace std;
	vector<string> sub_units=to_lexical_units(unit,use_func);
	return create_ast_tree(sub_units,0, sub_units.size(), use_func);
}


double moon::AbstractSyntaxTree::get_value(bool use_func)
{
	return _get_value(root,use_func);
}

double moon::AbstractSyntaxTree::_get_value(ast_node& node,bool usr_func)
{
	auto type = get_unit_type(node.unit,usr_func);
	if (type == nodeType::value)
		return stod(node.unit);
	else if (type == nodeType::variable) {
		if (custom_variable.find(node.unit) != custom_variable.end())
			return custom_variable.find(node.unit)->second;
		else
			return argv.find(node.unit)->second;
	}
	else if (type == nodeType::base_op) {
		//+ - * /
		if (node.unit == "+") {
			return _get_value(node.children[0],usr_func) + _get_value(node.children[1],usr_func);
		}
		else if (node.unit == "-") {
			if (node.children_num == 2)
				return _get_value(node.children[0], usr_func) - _get_value(node.children[1], usr_func);
			else
				return -_get_value(node.children[0], usr_func);
		}
		else if (node.unit == "*") {
			return _get_value(node.children[0], usr_func) * _get_value(node.children[1], usr_func);
		}
		else if (node.unit == "/") {
			if (_get_value(node.children[1], usr_func) == 0) throw division_zero();
			return _get_value(node.children[0], usr_func) / _get_value(node.children[1], usr_func);
		}
		else if (node.unit == "^") {
			return pow(_get_value(node.children[0], usr_func) , _get_value(node.children[1], usr_func));
		}
		else {
			throw unkown_op();
		}
	}
	else if (type == nodeType::base_fun) {
		if (node.unit == "sin") {
			return sin(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "cos") {
			return cos(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "tan") {
			return tan(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "arccos") {
			if (_get_value(node.children[0], usr_func) > 1 || _get_value(node.children[0], usr_func) < -1)
				throw arc_range();
			return acos(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "arcsin") {
			if (_get_value(node.children[0], usr_func)>1 || _get_value(node.children[0], usr_func)<-1)
				throw arc_range();
				return asin(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "arctan") {
				return atan(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "log") {
			if (_get_value(node.children[0], usr_func) <= 0)
				throw log_negtive();
			return log2(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "ln") {
			if (_get_value(node.children[0], usr_func) <= 0)
				throw log_negtive();
			return log(_get_value(node.children[0], usr_func));
		}
		else if (node.unit == "lg") {
			if (_get_value(node.children[0], usr_func) <= 0)
				throw log_negtive();
			return log10(_get_value(node.children[0], usr_func));
		}
	}
	else if (type == nodeType::functor_) {
		//传递参数引用，调用moon::my_functor::get_value
		auto fun = custom_function.find(node.unit)->second;
		int num = 0;
		for (auto &argument : fun.ast.argv) {
			argument.second = _get_value(node.children[num], true);
			++num;
		}
		return fun.get_value();
	}
	return 0.0;
}

bool moon::AbstractSyntaxTree::is_in_bracket(vector<string> &units,int begin, int end, int pos)
{
	int before = 0, after = 0;
	for (int i = pos - 1; i >= begin; --i)
	{
		if (units[i] == "(") ++before;
		else if (units[i] == ")") --before;
	}
	if (before == 0)	return false;
	else return true;
	return false;
}

bool moon::AbstractSyntaxTree::is_negtive(vector<string> &units,int pos)
{
	if (pos == 0) return true;
	auto type = get_unit_type(units[pos - 1]);
	if (units[pos - 1] == ")") return false;
	if (type == nodeType::value || type == nodeType::variable)
		return false;
	return true;

}

std::vector<std::string> moon::AbstractSyntaxTree::to_lexical_units(const std::string & text, bool use_func)
{
	using namespace std;
	std::vector<std::string> tem_return_vec;
	string tem_regex;
	for (auto &entry : custom_function)
		tem_regex += string("(") + entry.first + string(")|");
	for (auto &entry : custom_variable)
		tem_regex += string("(") + entry.first + string(")|");
	for (auto &entry : base_fun_priority) {
		tem_regex += string("(") + entry.first + string(")|");
	}
	for (auto &entry : base_op_priority) {
		tem_regex += string("(\\") + entry.first + string(")|");
	}
	if (use_func) {
		for (auto &entry : argv) {
			tem_regex += string("(") + entry.first + string(")|");
		}
	}

	tem_regex.pop_back();
	tem_regex.append("|([0-9,\\.]+)|(\\,)");
	std::vector<string> units;
	std::regex re(tem_regex);
	std::sregex_iterator ite(text.begin(), text.end(), re);
	for (; ite != sregex_iterator(); ++ite)
		if (ite->str() != " ")
			tem_return_vec.push_back(ite->str());
	if (tem_return_vec.empty())
		throw unkown_signal();
	vector<string> return_vec;
	for (auto ite = tem_return_vec.begin(); ite != tem_return_vec.end()-1; ++ite) {
		return_vec.push_back(*ite);
		auto cur_type = get_unit_type(*ite);
		if (cur_type == nodeType::value || cur_type == nodeType::variable) {
			auto next_type = get_unit_type(*(ite+1));
			if (next_type != nodeType::base_op)
				return_vec.push_back("*");
		}
	}
	return_vec.push_back(tem_return_vec.back());
	return move(return_vec);
}

moon::nodeType moon::AbstractSyntaxTree::get_unit_type(std::string & text, bool use_func)
{
	if (base_fun_priority.find(text) != base_fun_priority.end()) return nodeType::base_fun;
	if (base_op_priority.find(text) != base_op_priority.end()) return nodeType::base_op;
	if (custom_function.find(text) != custom_function.end()) return nodeType::functor_;
	if (custom_variable.find(text) != custom_variable.end()) return nodeType::variable;
	if (use_func&&argv.find(text) != argv.end()) return nodeType::variable;
	try {
		//这里不能用异常来判断是否非法
		auto units=to_lexical_units(text,true);
		if (units.size() != 1) return nodeType::expression;
		auto tem = stod(text);
		return nodeType::value;
	}
	catch (exception &e) {
		return nodeType::invalid;
	}
}
