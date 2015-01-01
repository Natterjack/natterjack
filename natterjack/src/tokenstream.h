// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------
#pragma once

#include "lexer.h"

#include <string>

namespace natterjack
{
	// TokenStream
	//
	// A source of tokens. Represents the current file or buffer being compiled.
	class TokenStream
	{
	public:
		virtual ~TokenStream();

		static TokenStream createFromString(const std::string& input);
		static TokenStream createFromStream(std::istream& input);

		virtual Token* next();
		
	private:
		TokenStream(std::istream& input);
		Lexer lexer;
	};

}
