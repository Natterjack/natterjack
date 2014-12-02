// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include "parser.h"
#include "tokenstream.h"

#include <iostream>

namespace natterjack {

	Parser::Parser(TokenStream* ts)
		: tokenStream(ts)
	{ }

	Parser::~Parser()
	{ }
	
	void Parser::parse() {
		Token* tok;
		do {
			tok = tokenStream->next();
			std::cout << *tok << std::endl;
		} while (tok->type != natterjack::Token::END &&
				 tok->type != natterjack::Token::ERROR);
	}
}
