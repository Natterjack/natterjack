// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#pragma once

#include <string>

namespace natterjack
{
	struct Token;

	class Lexer
	{
	public:
		Lexer(std::string buffer);
		Token* next();

	private:
		// Ragel's stuff
		// buffer state
		const char* p, * pe, * eof;
		// current token
		const char* ts, * te;
		// machine state
		int act, cs, top, stack[1];

		// our 'buffer'
		std::string buffer;
	};
}
