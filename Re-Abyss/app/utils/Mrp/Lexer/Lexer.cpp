#include "Lexer.hpp"
#include <Siv3D.hpp>

namespace Mrp
{
    Lexer::Lexer(s3d::FilePathView mns)
    {
        this->load(mns);
    }
	Lexer::Lexer(s3d::Arg::code_<s3d::String> code)
	{
		this->load(code);
	}
	bool Lexer::load(s3d::FilePathView mns)
	{
		TextReader reader(mns);
		if (!reader) {
			return false;
		}
		String line;
		while (reader.readLine(line)) {
			if (line[0] == ';') {
				// コメント
				continue;
			}

			// パース
			this->parseLine(line);
		}

		return true;
	}
	bool Lexer::load(s3d::Arg::code_<s3d::String> code)
	{
		for (auto&& line : code->split(U'\n')) {
			if (line[0] == ';') {
				// コメント
				continue;
			}

			// パース
			this->parseLine(line);
		}
		return true;
	}
	void Lexer::parseLine(const s3d::String& line)
	{
		size_t pos = 0;
		const size_t length = line.length();
		bool m_isTitle = false;
		while (pos < length) {
			// 空白スキップ
			while (IsSpace(line[pos])) {
				++pos;
			}
			if (!m_isTitle && (IsAlpha(line[pos]) || line[pos] == U'@')) {
				// 識別子
				const size_t start = pos;
				++pos;

				while (pos < length && (IsAlnum(line[pos]) || line[pos] == U'_')) {
					++pos;
				}
				m_tokens.emplace_back(TokenType::Ident, line.substr(start, pos - start));
			} else if (line[pos] == L'"') {
				// 文字列

				++pos;
				const size_t start = pos;
				while (pos < length) {
					if (line[pos] == U'\"' && line[pos - 1] != U'\\') {
						break;
					}
					++pos;
				}
				String text = line.substr(start, pos - start).replace(U"\\\"", U"\"");
				m_tokens.emplace_back(TokenType::Value, std::move(text));
				++pos;
			} else if (line[pos] == U'-') {
				m_tokens.emplace_back(TokenType::Bar, String(1, line[pos]));
				++pos;
			} else if (line[pos] == U'[') {
				m_tokens.emplace_back(TokenType::LSqBrace, String(1, line[pos]));
				++pos;
				m_isTitle = true;
			} else if (line[pos] == U']') {
				m_tokens.emplace_back(TokenType::RSqBrace, String(1, line[pos]));
				++pos;
				m_isTitle = false;
			} else if(m_isTitle) {
				const size_t start = pos;
				while (pos < length) {
					if (IsSpace(line[pos]) || line[pos] == U'[' || line[pos] == U']') {
						break;
					}
					++pos;
				}
				m_tokens.emplace_back(TokenType::Value, line.substr(start, pos - start));
			}
		}
	}
}