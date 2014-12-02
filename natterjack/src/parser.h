// ---------------------------------------------------------------------------
// 
//    Project Natterjack - Statically Typed Language, Compiler and Runtime
// 
// This file is distributed under the open source MIT license. See LICENSE.md
// for more info.
// 
// ---------------------------------------------------------------------------

#pragma once


namespace natterjack {
	
	class TokenStream;

	class Parser {
	public:
		Parser(TokenStream* tokenStream);
		virtual ~Parser();

		void parse();

	private:
		TokenStream* tokenStream;
	};
}
