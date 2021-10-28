#include "Lexer.hpp"
#include <Siv3D.hpp>
#include <locale>

namespace Mns
{
    Lexer::Lexer(const s3d::FilePath& mns)
    {
        this->load(mns);
    }
	bool Lexer::load(const FilePath& mns)
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
	void Lexer::parseLine(const s3d::String& line)
	{
		size_t pos = 0;
		const size_t length = line.length();
		bool m_isTag = false;
		while (pos < length) {
			// 空白スキップ
			while (IsSpace(line[pos])) {
				++pos;
			}
			if (m_isTag && IsAlpha(line[pos])) {
				// 識別子
				const size_t start = pos;
				while (pos < length && (IsAlnum(line[pos]) || line[pos] == U'_')) {
					++pos;
				}
				m_tokens.emplace_back(TokenType::Ident, line.substr(start, pos - start));
			} else if (m_isTag && IsDigit(line[pos]) || line[pos] == U'-' && pos + 1 < length && IsDigit(line[pos + 1])) {
				// 数
				const size_t start = pos;
				bool isFoundDot = false;

				++pos;
				while (pos < length) {
					if (IsDigit(line[pos])) {
						++pos;
					} else if (!isFoundDot && line[pos] == U'.' && pos + 1 < length && IsDigit(line[pos + 1])) {
						isFoundDot = true;
						pos += 2;
					} else {
						break;
					}
				}
				m_tokens.emplace_back(TokenType::Value, line.substr(start, pos - start));
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
				m_tokens.emplace_back(m_isTag ? TokenType::Value : TokenType::Text, std::move(text));
				++pos;
			} else if (line[pos] == U'[') {
				m_tokens.emplace_back(TokenType::LSqBrace, String(1, line[pos]));
				++pos;
				m_isTag = true;
			} else if (line[pos] == U']') {
				m_tokens.emplace_back(TokenType::RSqBrace, String(1, line[pos]));
				++pos;
				m_isTag = false;
			} else if (line[pos] == U'=') {
				m_tokens.emplace_back(TokenType::Assign, String(1, line[pos]));
				++pos;
				m_isTag = false;
			} else {
				// 何もなければ文章
				const size_t start = pos;
				while (pos < length) {
					if (IsSpace(line[pos]) || line[pos] == U'[' || line[pos] == U']') {
						break;
					}
					++pos;
				}
				m_tokens.emplace_back(m_isTag ? TokenType::Value : TokenType::Text, line.substr(start, pos - start));
			}
		}
	}
}