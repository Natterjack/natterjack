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
#include <ostream>
#include <istream>

#define TOKEN_TYPES(expr)						\
	expr(ERROR, -1)								\
	expr(UNDEFINED, 0)							\
	expr(OP_ADD, 1)								\
	expr(OP_INCREMENT, 2)						\
	expr(OP_SUB, 3)								\
	expr(OP_DECREMENT, 4)						\
	expr(OP_MUL, 5)								\
	expr(OP_DIV, 6)								\
	expr(OP_EQ, 7)								\
	expr(OP_NEQ, 8)								\
	expr(OP_ASSIGN, 9)							\
	expr(INTEGER, 10)							\
	expr(IDENTIFIER, 11)						\
	expr(END, 12)

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
	std::ostream& operator << (std::ostream& stream, const Token::TokenType& type);

	class Lexer
	{
	public:
		Lexer(std::istream& input);
		Token* next();

	private:
		// Ragel's stuff
		// buffer state
		const char* p, * pe, * eof;
		// current token
		const char* ts, * te;
		// machine state
		int act, cs, top, stack[1];

		std::string buffer;
	};
}
