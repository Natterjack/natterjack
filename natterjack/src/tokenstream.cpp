// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include <string>
#include <sstream>
#include <iostream>

#include "lexer.h"
#include "tokenstream.h"

using namespace natterjack;

TokenStream::TokenStream(std::istream& stream)
	: lexer(stream)
{
}

TokenStream::~TokenStream()
{
}

TokenStream TokenStream::createFromString(const std::string& input)
{
	std::stringstream buffer(input);
	return TokenStream(buffer);
}

TokenStream TokenStream::createFromStream(std::istream& input)
{
	return TokenStream(input);
}

Token* TokenStream::next()
{
	return lexer.next();
}
