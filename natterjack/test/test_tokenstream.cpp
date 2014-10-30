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
