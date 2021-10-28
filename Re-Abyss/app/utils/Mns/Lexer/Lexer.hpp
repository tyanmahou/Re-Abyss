#pragma once
#include "Token.hpp"
#include <Siv3D/String.hpp>
#include <Siv3D/Array.hpp>

namespace Mns
{
	class Lexer
	{
	public:
		Lexer(const s3d::FilePath& mns);

		bool load(const s3d::FilePath& ctfolder);

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
