#include <abyss/utils/NeptScript/Script/Lexer/Lexer.hpp>
#include <Siv3D.hpp>

namespace abyss::Nept
{
    Lexer::Lexer(const s3d::FilePath& mns)
    {
        this->load(mns);
    }
    Lexer::Lexer(s3d::Arg::code_<s3d::String> code)
    {
        this->load(code);
    }
    bool Lexer::load(const FilePath& mns)
    {
        TextReader reader(mns);
        if (!reader) {
            return false;
        }
        String line;
        while (reader.readLine(line)) {
            // パース
            this->parseLine(line);
        }

        return true;
    }
    bool Lexer::load(s3d::Arg::code_<s3d::String> code)
    {
        for (auto&& line : code->split(U'\n')) {
            // パース
            this->parseLine(line);
        }
        return true;
    }
    void Lexer::parseLine(const s3d::String& line)
    {
        size_t pos = 0;
        const size_t length = line.length();

        // 事前
        // 空白スキップ
        while (IsSpace(line[pos])) {
            ++pos;
        }
        if (pos >= length) {
            return;
        }

        bool isText = false;
        bool isCommand = false;
        // 行の最初が一部記号の場合はテキストではない
        if (line[pos] == U'#' ||
            line[pos] == U'@' ||
            line[pos] == U'{' ||
            line[pos] == U'}' ||
            line[pos] == U'/' ||
            line[pos] == U'\\'||
            line[pos] == U'|' ||
            false
        ) {
            isText = false;
        } else {
            isText = true;
        }

        while (pos < length) {
            // 空白スキップ
            while (IsSpace(line[pos])) {
                ++pos;
            }
            if (pos >= length) {
                return;
            }
            if (line[pos] == U';') {
                // コメント
                return;
            }
            if (!isText && IsAlpha(line[pos])) {
                // 識別子
                const size_t start = pos;
                ++pos;

                while (pos < length && (IsAlnum(line[pos]) || line[pos] == U'_' || line[pos] == U'-')) {
                    ++pos;
                }
                auto tokenType = TokenType::Value;
                if (isCommand) {
                    // コマンドモード
                    auto prevToken = m_tokens.back().type;
                    if (prevToken != TokenType::Colon) {
                        // 直前がコロンじゃなければ識別子
                        tokenType = TokenType::Ident;
                    }
                }
                m_tokens.emplace_back(tokenType, line.substr(start, pos - start));
            } else if (!isText && IsDigit(line[pos]) || line[pos] == U'-' && pos + 1 < length && IsDigit(line[pos + 1])) {
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
                m_tokens.emplace_back(isText ? TokenType::Text : TokenType::Value, std::move(text));
                ++pos;
            } else if (line[pos] == U'@') {
                m_tokens.emplace_back(TokenType::At, String(1, line[pos]));
                isCommand = true;
                ++pos;
            } else if (line[pos] == U'[') {
                m_tokens.emplace_back(TokenType::LBracket, String(1, line[pos]));
                ++pos;
                isCommand = true;
                isText = false;
            } else if (line[pos] == U']') {
                m_tokens.emplace_back(TokenType::RBracket, String(1, line[pos]));
                ++pos;
                isCommand = false;
                isText = true;
            } else if (line[pos] == U'{') {
                m_tokens.emplace_back(TokenType::LBrace, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U'}') {
                m_tokens.emplace_back(TokenType::RBrace, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U':') {
                m_tokens.emplace_back(TokenType::Colon, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U'#') {
                m_tokens.emplace_back(TokenType::Sharp, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U'/') {
                m_tokens.emplace_back(TokenType::Slash, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U'\\') {
                m_tokens.emplace_back(TokenType::BackSlash, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U'|') {
                m_tokens.emplace_back(TokenType::Pipe, String(1, line[pos]));
                ++pos;
            } else if (line[pos] == U'.') {
                m_tokens.emplace_back(TokenType::Dot, String(1, line[pos]));
                ++pos;
            }  else {
                // 何もなければテキスト
                const size_t start = pos;
                while (pos < length) {
                    if (line[pos] == U'[' || line[pos] == U']') {
                        break;
                    }
                    ++pos;
                }
                auto text = line.substr(start, pos - start);
                if (!text.isEmpty()) {
                    m_tokens.emplace_back(isText ? TokenType::Text : TokenType::Value, line.substr(start, pos - start));
                }
            }
        }
    }
}
