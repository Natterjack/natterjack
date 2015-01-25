#include <gtest/gtest.h>
#include "parser.h"
#include "tokenstream.h"

using namespace natterjack;

TEST(Parser,Create) {
	auto stream = TokenStream::createFromString("hello world");

	Parser* created = new Parser(&stream);
	ASSERT_NE(nullptr, created);
}

TEST(Parser, UtilityMethods) {

	// Check we can parse strings diretly into trees.
	Expression* parsed = Parser::parse("1337");
	ASSERT_NE(nullptr, parsed);
}
