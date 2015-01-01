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
#include "expressions.h"

#include <iostream>
#include <sstream>
#include <exception>
#include <map>

namespace natterjack
{

namespace
{
	typedef Expression* (&PrefixParselet)(Parser& parser, Token* token);

	Expression* NumberParselet(Parser& parser, Token* token)
	{
		int value = std::stoi(token->value);
		return Expression::valueExpression(value);
	}

	Expression* DecimalParselet(Parser& parser, Token* token)
	{
		double value = std::stod(token->value);
		return Expression::valueExpression(value);
	}

	Expression* BoolParselet(Parser& parser, Token* token)
	{
		static const std::string trueString = "true";
		bool value = token->value == trueString;
		return Expression::valueExpression(value);
	}

	Expression* StringParselet(Parser& parser, Token* token)
	{
		return Expression::valueExpression(token->value);
	}

	const std::map<Token::TokenType, PrefixParselet> prefixTypes = {
		{ Token::INTEGER, NumberParselet },
		{ Token::IDENTIFIER, StringParselet }
	};

	// TODO: Add infix parsing for operators
	// struct InfixParselet
	// {
	// 	InfixParselet(int bindingPower)
	// 		: power(bindingPower)
	// 	{}
	// 	virtual ~InfixParselet() = 0;

	// 	virtual Expression* parse(
	// 		Parser& parser, Expression* lhs Token* token) = 0;

	// 	int power;
	// };

	// struct BinOpParselet : InfixParselet
	// {
	// 	Expression* parse(Parser& parser, Expression* lhs Token* token)
	// 	{
	// 		auto rhs = parser.parseExpression(0);
	// 		return Expression::binaryExpression(lhs, OperatorType::MUL, rhs);
	// 	}
	// };

	// const std::map<Token::TokenType, InfixParselet> infixTypes = {
		
	// };
	
}

	Parser::Parser(TokenStream* ts)
		: tokenStream(ts)
	{ }

	Parser::~Parser()
	{ }
	
	std::list<Expression*> Parser::parse()
	{
		std::list<Expression*> ret;

		for (auto tok = tokenStream->peek(); tok && tok->type != Token::END;
			 tok = tokenStream->peek())
		{
			ret.push_back(parseExpression(0));
		}

		return ret;
	}

	Expression* Parser::parseExpression(int bindingPower)
	{
		auto tok = tokenStream->next();

		auto parselet = prefixTypes.find(tok->type);

		if (parselet == prefixTypes.end())
		{
			std::stringstream err("parse error: ");
			err << "expecting ";
			for (auto parselet : prefixTypes)
			{
				err << parselet.first << ", ";
			}
				
			err << "found " << *tok;
			throw std::logic_error(err.str());
		}

		auto lhs = parselet->second(*this, tok);

		

		return lhs;
	}
}
