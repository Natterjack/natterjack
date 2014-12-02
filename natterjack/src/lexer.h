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

#define TOKEN_TYPES(expr)						\
	expr(ERROR, -1)								\
	expr(UNDEFINED, 0)							\
	expr(OPERATOR, 1)							\
	expr(INTEGER, 2)							\
	expr(IDENTIFIER, 3)							\
	expr(END, 4)								\

namespace natterjack
{
	// Token
	//
	// Represents a single lexeme from an input stream.
	struct Token
	{
#define DEFINE(name, value) name = value,
		enum TokenType {
			TOKEN_TYPES(DEFINE)
		};
#undef DEFINE

		TokenType type;
		std::string value;
	};

	std::ostream& operator << (std::ostream& stream, const Token& token);

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
