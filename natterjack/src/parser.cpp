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

	typedef std::map<Token::TokenType, PrefixParselet> PrefixParseletMap;
	const PrefixParseletMap prefixTypes = {
		{ Token::INTEGER, NumberParselet },
		{ Token::IDENTIFIER, StringParselet }
	};

	struct InfixParselet
	{
		InfixParselet(int bindingPower)
			: power(bindingPower)
		{}

		virtual ~InfixParselet()
		{}

		virtual Expression* parse(
			Parser& parser, Expression* lhs, Token* token) = 0;

		int power;
	};

	struct BinOpParselet : public InfixParselet
	{
		BinOpParselet(int bindingPower, OperatorType op)
			: InfixParselet(bindingPower), op(op)
		{}

		Expression* parse(Parser& parser, Expression* lhs, Token* token)
		{
			auto rhs = parser.parseExpression(power);
			return Expression::binaryExpression(lhs, op, rhs);
		}

	private:
		OperatorType op;
	};

	std::map<Token::TokenType, InfixParselet*> infixTypes = {

		// Asssignment here at 1

		{ Token::OP_EQ, new BinOpParselet(2, OperatorType::EQ) },
		{ Token::OP_NEQ, new BinOpParselet(2, OperatorType::NOT_EQ) },

		{ Token::OP_ADD, new BinOpParselet(3, OperatorType::ADD) },
		{ Token::OP_SUB, new BinOpParselet(3, OperatorType::SUB) },

		{ Token::OP_MUL, new BinOpParselet(4, OperatorType::MUL) },
		{ Token::OP_DIV, new BinOpParselet(4, OperatorType::DIV) },
	};


	class ParseError : public std::logic_error
	{
	public:
		ParseError(const PrefixParseletMap& expecting, Token* found)
			: std::logic_error(errorMessage(expecting, found))
		{}

	private:
		static std::string errorMessage(
			const PrefixParseletMap& expecting, Token* found)
		{
			std::stringstream err;

			err << "parse error: expecting ";

			bool comma = false;
			for (auto parselet : expecting)
			{
				if (comma)
					err << ", ";
				err << parselet.first;
				comma = true;
			}

			err << " found " << *found;

			return err.str();
		}
	};
	
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
			throw ParseError(prefixTypes, tok);
		}

		auto lhs = parselet->second(*this, tok);

		// if we can't find an operator parselet we will return the
		// 'left-hand-side' directly as the whole expression,
		// otherwise we will repeatedly 'tack-on' right-hand-sides
		// while the binding power allows us
		for (auto opParselet = infixTypes.find(tokenStream->peek()->type);
			 opParselet != infixTypes.end() && bindingPower < opParselet->second->power;
			 opParselet = infixTypes.find(tokenStream->peek()->type))
		{
			tok = tokenStream->next();
			lhs = opParselet->second->parse(*this, lhs, tok);
		}

		return lhs;
	}
}
