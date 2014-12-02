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

			natterjack::TokenStream stream =
				natterjack::TokenStream::createFromStream(input);

			natterjack::Token* tok;
			do {
				tok = stream.next();
				std::cout << *tok << std::endl;
			} while (tok->type != natterjack::Token::END &&
				   tok->type != natterjack::Token::ERROR);

		}
		return 0;
	}
};

#ifndef UNIT_TEST
extern "C" int main(int argc, const char* argv[]) {

	// Your streams have no meaning here... :-p
	std::ostream::sync_with_stdio(false);

	Application::ParameterList args;

	for (int i = 1; i < argc; i++)
	{
		args.push_back(std::string(argv[i]));
	}

	return Application::main(args);
}
#endif
