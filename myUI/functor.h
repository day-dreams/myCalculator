#pragma once
#include"encode.h"
#include"abstractSyntaxTree.h"
#include<queue>
#include<string>
#include<unordered_map>

namespace moon {
	class my_functor {
		int argc;
	public:
		string markup;
		AbstractSyntaxTree ast;
		my_functor();
		my_functor(std::string text);
		double get_value();
	};
}
