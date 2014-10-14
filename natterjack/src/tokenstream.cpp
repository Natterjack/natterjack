// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include <string>
#include <iostream>

#include "lexer.h"
#include "tokenstream.h"

using namespace natterjack;

TokenStream::TokenStream(std::string input)
	: lexer(input)
{
}

TokenStream::TokenStream()
	: lexer("")
{
}

TokenStream::~TokenStream()
{
}

TokenStream TokenStream::createFromString(const std::string& input)
{
	return TokenStream(input);
}

Token* TokenStream::next()
{
	return lexer.next();
}
