// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include "lexer.h"
#include "tokenstream.h"

#include <cstdlib>

#include <string>
#include <iostream>

#define SET_TOKEN(t) token->type = Token::t;

%%{
  machine NatterjackLexer;

  main := |*

	# Decimal number literal
    digit+ => {
	  auto stuff = std::string(ts, te-ts);
	  token->iValue = atoi(stuff.c_str());
	  SET_TOKEN(INTEGER);
	  fbreak;
    };
	
    space+;
  *|;
  
}%%

%%write data;

using namespace natterjack;

Lexer::Lexer(std::string s)
	: buffer(s), cs(0), act(0), top(0)
{
	%%write init;

	// set up the buffer here
	p = buffer.c_str();
	pe = p + buffer.size();
	eof = pe;
}
	
Token* Lexer::next()
{
	auto token = new Token();

	token->type = Token::UNDEFINED;

	do {

		if (cs >= NatterjackLexer_first_final) {
			SET_TOKEN(END);
		}

		%%write exec;
		
		if (cs == NatterjackLexer_error) {
			SET_TOKEN(ERROR);
		}

		
	} while (token->type == Token::UNDEFINED);

	return token;
}
