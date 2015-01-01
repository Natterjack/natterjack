// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#pragma once

#include <string>

namespace natterjack
{

#define OPERATORS(expr)						\
	expr(ADD, "ADD"),						\
	expr(SUB, "SUB"),						\
	expr(MUL, "MUL"),						\
	expr(DIV, "DIV"),						\
	expr(GT, "GT"),							\
	expr(LT, "LT"),							\
	expr(GT_EQ, "GT_EQ"),					\
	expr(LT_EQ, "LT_EQ"),					\
	expr(OR, "OR"),							\
	expr(AND, "AND"),						\
	expr(NOT, "NOT"),						\
	expr(EQ, "EQ"),							\
	expr(NOT_EQ, "NOT_EQ"),					\
	expr(BIT_NOT, "BIT_NOT"),				\
	expr(BIT_OR, "BIT_OR"),					\
	expr(BIT_AND, "BIT_AND"),				\
	expr(BIT_XOR, "BIT_XOR"),				\
	expr(INC, "INC"),						\
	expr(DEC, "DEC"),						\
	expr(INDEX, "INDEX"),					\
	expr(CALL, "CALL")

enum class OperatorType
{
#define enum_val(value, name) value
	OPERATORS(enum_val)
#undef enum_val
};

namespace operator_utils
{
	const std::string& getName(OperatorType op);
}

struct Expression
{
	// write a representation of the expression to `cout` for debugging
	virtual void dump() = 0;

	// ValueExpression factory functions
	static Expression* valueExpression(const std::string& value);
	static Expression* valueExpression(int value);
	static Expression* valueExpression(bool value);
	static Expression* valueExpression(double value);

	// BinOpExpression factory function
	static Expression* binaryExpression(
		Expression* lhs, OperatorType op, Expression* rhs);

	// UnaryOpExpression factory function
	static Expression* prefixExpression(OperatorType op, Expression* expr);
	static Expression* postfixExpression(OperatorType op, Expression* expr);

	// polymorphic interface
	virtual ~Expression() {};
protected:
	Expression() {}
};
}
