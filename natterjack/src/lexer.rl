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
#include <sstream>

#define CAPTURE_TOKEN(t) \
	token->value = std::string(ts, te-ts); \
	SET_TOKEN(t)
#define SET_TOKEN(t) \
	token->type = Token::t

%%{
  machine NatterjackLexer;

  main := |*

	digit+ => {
	  CAPTURE_TOKEN(INTEGER);
	  fbreak;
    };

    alpha (alpha | digit) * => {
	  CAPTURE_TOKEN(IDENTIFIER);
	  fbreak;
    };

    opchar = [+\-*/=];
		
    opchar+ => {
		CAPTURE_TOKEN(OPERATOR);
		fbreak;
	};

	"#"[^\n]* => {
		// ignore comments
	};

    space+;
  *|;
  
}%%

%%write data;

using namespace natterjack;

Lexer::Lexer(std::istream& input)
	: cs(0), act(0), top(0)
{
	%%write init;

	// TODO: don't read all of the buffer here, read from it as needed.
	std::stringstream sBuf;
	sBuf << input.rdbuf();

	buffer = sBuf.str();

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
