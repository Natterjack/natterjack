#include <gtest/gtest.h>

#include "tokenstream.h"

using namespace natterjack;

TEST(TokenStream,Create) {
	auto ts = TokenStream::createFromString("");
	
	ts = TokenStream::createFromString("\0");
}

TEST(TokenStream,EndOfFile) {
	auto ts = TokenStream::createFromString("");

	auto token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);

	// should just keep on getting more end tokens once we have got
	// there
	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);
}

TEST(TokenStream,Integers) {
	auto integers = std::string("1 2 3 23 232332");
	auto ts = TokenStream::createFromString(integers);

	auto token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("1", token->value);

	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("2", token->value);

	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("3", token->value);

	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("23", token->value);

	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::INTEGER, token->type);
	EXPECT_EQ("232332", token->value);

	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);

	token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::END, token->type);
}

TEST(Tokenstream,Identifiers) {
	auto identifiers = "foo bar baz buzz";
	auto ts = TokenStream::createFromString(identifiers);

	auto token = ts.next();
	ASSERT_NE(nullptr, token);
	EXPECT_EQ(Token::IDENTIFIER, token->type);
	EXPECT_EQ("foo", token->value);
}
