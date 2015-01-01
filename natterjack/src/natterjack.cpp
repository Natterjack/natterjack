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
#include "parser.h"
#include "expressions.h"

using namespace natterjack;

class Application
{
public:
	typedef std::vector<std::string> ParameterList;

	static int main(const ParameterList& args)
	{
		for (auto arg : args) {
			std::cout << "parsing '" << arg << "'" << std::endl;
			std::ifstream input(arg);

			TokenStream stream =
				TokenStream::createFromStream(input);

			for (auto expr : Parser(&stream).parse())
			{
				expr->dump();
				std::cout << std::endl; // make sure there is a newline
			}
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
