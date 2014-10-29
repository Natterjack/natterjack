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
	// Token
	//
	// Represents a single lexeme from an input stream.
	struct Token
	{
		enum {
			ERROR = -1,
			UNDEFINED = 0,
			OPERATOR,
			INTEGER,
			IDENTIFIER,
			END
		} type;
		std::string value;
	};

	// TokenStream
	//
	// A source of tokens. Represents the current file or buffer being compiled.
	class TokenStream
	{
	public:
		virtual ~TokenStream();

		static TokenStream createFromString(const std::string& input);

		virtual Token* next();
		
	protected:
		// Instances should be created with the factory function
		TokenStream();
	private:
		TokenStream(std::string input);
		Lexer lexer;
	};

}
