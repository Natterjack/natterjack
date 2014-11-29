// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>

#include "tokenstream.h"

class Application
{
public:
	typedef std::vector<std::string> ParameterList;

	static int main(ParameterList args)
	{
		for (auto arg : args) {
			std::cout << "parsing '" << arg << "'" << std::endl;
			std::ifstream input(arg);
			natterjack::TokenStream stream = natterjack::TokenStream::createFromStream(input);
			auto tok = stream.next();
			while (tok->type != natterjack::Token::END &&
				   tok->type != natterjack::Token::ERROR)
			{
				std::cout << tok->value << std::endl;
				tok = stream.next();
			}
		}
		return 0;
	}
};

#ifndef UNIT_TEST
extern "C" int main(int argc, const char* argv[]) {

	Application::ParameterList args;

	for (int i = 1; i < argc; i++)
	{
		args.push_back(std::string(argv[i]));
	}

	return Application::main(args);
}
#endif
