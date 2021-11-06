#pragma once
#include "Token.hpp"
#include <Siv3D/String.hpp>
#include <Siv3D/Array.hpp>

namespace Mrp
{
	class Lexer
	{
	public:
		Lexer(s3d::FilePathView mns);
		Lexer(s3d::Arg::code_<s3d::String> code);

		bool load(s3d::FilePathView ctfolder);
		bool load(s3d::Arg::code_<s3d::String> code);

		const s3d::Array<Token>& getTokens()const
		{
			return m_tokens;
		}
	private:
		void parseLine(const s3d::String& line);
	private:
		s3d::Array<Token> m_tokens;
	};
}
