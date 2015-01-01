// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#include "expressions.h"

#include <iostream>
#include <map>

namespace natterjack
{
	namespace operator_utils
	{
		static std::map<OperatorType, std::string> opNames = {
#define expand_name(value, name) { OperatorType::value, name }
			OPERATORS(expand_name)
#undef expand_name
		};

		const std::string& getName(OperatorType op)
		{
			return opNames[op];
		}
	}

	struct StringExpression : Expression
	{
		StringExpression(const std::string& value)
			: value(value)
		{}


		void dump()
		{
			std::cout << '"' << value << '"';
		}

		std::string value;
	};

	Expression* Expression::valueExpression(const std::string& value)
	{
		return new StringExpression(value);
	}

	template <typename T>
	struct SimpleValueExpression : Expression
	{
		SimpleValueExpression(T value)
			: value(value)
		{}
		
		void dump()
		{
			std::cout << value;
		}

		T value;
	};

	typedef SimpleValueExpression<int> NumberExpression;

	Expression* Expression::valueExpression(int value)
	{
		return new NumberExpression(value);
	}

	typedef SimpleValueExpression<double> DecimalExpression;
	
	Expression* Expression::valueExpression(double value)
	{
		return new DecimalExpression(value);
	}

	typedef SimpleValueExpression<bool> BoolExpression;

	Expression* Expression::valueExpression(bool value)
	{
		return new BoolExpression(value);
	}

	struct BinOpExpression : Expression
	{
		BinOpExpression(Expression* lhs, OperatorType op, Expression* rhs)
			: lhs(lhs), op(op), rhs(rhs)
		{}

		void dump()
		{
			std::cout << '(';
			lhs->dump();
			std::cout << ' ' << operator_utils::getName(op) << ' ';
			rhs->dump();
			std::cout << ')' << std::endl;
		}

		Expression* lhs, * rhs;
		OperatorType op;
	};

	Expression* Expression::binaryExpression(
		Expression* lhs, OperatorType op, Expression* rhs)
	{
		return new BinOpExpression(lhs, op, rhs);
	}

	struct UnaryOpExpression : Expression
	{
		enum Assoc { PREFIX, POSTFIX };

		UnaryOpExpression(OperatorType op, Expression* expr, Assoc assoc)
			: expression(expr), op(op), association(assoc)
		{}

		void dump()
		{
			std::cout << operator_utils::getName(op);
			expression->dump();
		}

		Expression* expression;
		OperatorType op;
		Assoc association;
	};

	Expression* Expression::prefixExpression(OperatorType op, Expression* expr)
	{
		return new UnaryOpExpression(op, expr, UnaryOpExpression::PREFIX);
	}

	Expression* Expression::postfixExpression(OperatorType op, Expression* expr)
	{
		return new UnaryOpExpression(op, expr, UnaryOpExpression::POSTFIX);
	}
}
