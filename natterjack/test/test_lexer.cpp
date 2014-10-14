#include <gtest/gtest.h>
#include "lexer.h"

using namespace natterjack;

TEST(Lexer,Create) {
	auto test = std::string("hello world");

	Lexer* lexer = new Lexer(test);
	ASSERT_NE(nullptr, lexer);
}
