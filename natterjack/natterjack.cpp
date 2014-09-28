// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include <iostream>
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
			natterjack::TokenStream stream = natterjack::TokenStream::createFromString(arg);
			auto tok = stream.next();
			while (tok != nullptr)
			{
				std::cout << tok << std::endl;
				tok = stream.next();
			}
		}
		return 0;
	}
};

extern "C" int main(int argc, const char* argv[]) {

	Application::ParameterList args;

	for (int i = 1; i < argc; i++)
	{
		args.push_back(std::string(argv[i]));
	}

	return Application::main(args);
}
