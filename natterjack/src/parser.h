// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#pragma once

#include <list>

namespace natterjack {
	
	class TokenStream;
	class Expression;

	class Parser {
	public:
		Parser(TokenStream* tokenStream);
		virtual ~Parser();

		std::list<Expression*> parse();
		Expression* parseExpression(int bindingPower);

	private:
		TokenStream* tokenStream;
	};
}
