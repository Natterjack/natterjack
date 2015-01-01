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
	: lexer(stream), buffered(nullptr)
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

Token* TokenStream::peek()
{
	if (!buffered)
		buffered = lexer.next();

	return buffered;
}

Token* TokenStream::chomp(Token::TokenType type)
{
	auto head = peek();

	if (head->type != type)
		return nullptr;

	return head;
}

Token* TokenStream::next()
{
	auto ret = peek();
	buffered = nullptr;
	return ret;
}
