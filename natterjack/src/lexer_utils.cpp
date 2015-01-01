// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include <ostream>
#include "lexer.h"

namespace natterjack {

	struct name_mapping {
		const char* name;
		Token::TokenType type;
	};

#define NAME(name, value) { #name, Token::name },
	name_mapping types[] = {
		TOKEN_TYPES(NAME)
	};
#undef NAME

	static const char* typeToName(Token::TokenType type) {
		for (auto mapping : types) {
			if (mapping.type == type)
				return mapping.name;
		}
		return "<UNKNOWN>";
	}

	std::ostream& operator << (
		std::ostream& stream, const Token::TokenType& type)
	{
		return stream << typeToName(type);
	}


	std::ostream& operator << (std::ostream& stream, const Token& token) {
		stream << "<Token " << typeToName(token.type);
		if (!token.value.empty())
			stream << " (" << token.value << ")";
		return stream << ">";
	}
}
