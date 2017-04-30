#include "functor.h"
#include"parserMachine.h"
#include<string>
#include<algorithm>

moon::my_functor::my_functor()
{
}

moon::my_functor::my_functor(std::string  text)
{
	auto pos = text.find("=");
	auto before = text.substr(0, pos);
	auto after = text.substr(pos+1);
	this->argc = count(before.begin(),before.end(),' ')+1;
	this->markup = before.substr(0,before.find("("));
	this->ast = AbstractSyntaxTree(text, true);
}

double moon::my_functor::get_value()
{
	return ast.get_value(true);
}
