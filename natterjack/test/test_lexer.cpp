#include <gtest/gtest.h>
#include "lexer.h"

using namespace natterjack;

static Lexer CreateLexer(std::string const & input) {
	return Lexer(input);
}

TEST(Lexer,Create) {
	auto test = std::string("hello world");

	Lexer* lexer = new Lexer(test);
	ASSERT_NE(nullptr, lexer);
}

TEST(Lexer,Integers) {
	auto integers = std::string("1 2 3 23 232332");
	auto lex = CreateLexer(integers);

	auto token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("1", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("2", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("3", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("23", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("232332", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);
}

TEST(Lexer,Identifiers) {
	auto identifiers = "foo bar baz buzz";
	auto lex = CreateLexer(identifiers);

	auto token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::IDENTIFIER, token->type);
	EXPECT_EQ("foo", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::IDENTIFIER, token->type);
	EXPECT_EQ("bar", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::IDENTIFIER, token->type);
	EXPECT_EQ("baz", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::IDENTIFIER, token->type);
	EXPECT_EQ("buzz", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);
}

TEST(Lexer,Operators) {
	auto ops = "+ - * / ++ == = -= +=";
	auto lex = CreateLexer(ops);

	auto token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("+", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("-", token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("*", token->value);



	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("/",token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("++",token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("==",token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("=",token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("-=",token->value);

	token = lex.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::OPERATOR, token->type);
	EXPECT_EQ("+=",token->value);
}
