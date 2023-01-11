#include <abyss/utils/Env/detail/EnvParser.hpp>

namespace
{
    enum MultilineType
    {
        SingleQuote = 1,
        DoubleQuote = 2,
    };

    // キーとして正しい識別子か
    bool IsKeyName(const s3d::String& s)
    {
        if (s.empty()) {
            return false;
        }
        if (!(IsAlpha(s[0]) || s[0] == U'_')) {
            return false;
        }
        for (size_t i = 1; i < s.size(); ++i) {
            if (!(IsAlnum(s[0]) || s[0] == U'_')) {
                return false;
            }
        }
        return true;
    }

    // コメント排除
    s3d::String RemoveComment(const s3d::String& s)
    {
        // 補完あり
        size_t pos = 0;
        size_t length = s.length();

        while (pos < length) {
            if (s[pos] == U'#') {
                // コメント
                break;
            }
            ++pos;
        }
        return s.substr(0, pos).trim();
    }
}
namespace abyss::detail
{
    EnvParser::EnvParser(std::unique_ptr<IEnvContainer>&& container):
        m_container(std::move(container))
    {
    }
    bool EnvParser::set(const s3d::String& key, const s3d::String& value, bool overwrite)
    {
        return m_container->set(key, value, overwrite);
    }
    s3d::String EnvParser::get(const s3d::String& key) const
    {
        return this->getOpt(key).value_or(U"");
    }
    s3d::Optional<s3d::String> EnvParser::getOpt(const s3d::String& key) const
    {
        return m_container->getOpt(key);
    }
    bool EnvParser::load(const s3d::String& path, bool overwrite)
    {

        s3d::TextReader file(path);
        if (!file) {
            return false;
        }

        s3d::String key;
        s3d::String value;
        s3d::String line;
        int32 multiLine = 0;
        while (file.readLine(line)) {
            if (multiLine > 0) {
                // マルチライン
                auto v = line.trim();
                if (multiLine == MultilineType::DoubleQuote && v == U"\"\"\"" || multiLine == MultilineType::SingleQuote && v == U"'''") {
                    // マルチライン解除
                    multiLine = 0;
                } else {
                    if (!value.isEmpty()) {
                        value += U"\n";
                    }
                    if (multiLine == MultilineType::DoubleQuote) {
                        value += this->interp(line.replaced(U"\\\"", U"\""));
                    } else if (multiLine == 2) {
                        value += line.replaced(U"\\'", U"'");
                    }
                }
            } else {
                auto eq = line.indexOf(U'=');
                if (eq == s3d::String::npos) {
                    continue;
                }
                // Key
                key = line.substr(0, eq).trim();
                if (!::IsKeyName(key)) {
                    continue;
                }
                // Value
                auto v = line.substr(eq + 1).trim();
                if (v == U"\"\"\"") {
                    multiLine = MultilineType::SingleQuote;
                    value.clear();
                } else if (v == U"'''") {
                    multiLine = MultilineType::DoubleQuote;
                    value.clear();
                } else {
                    value = this->parseValue(v);
                }
            }
            if (multiLine > 0) {
                // マルチライン中
                continue;
            }
            // 環境設定更新
            this->set(key, value, overwrite);
        }
        return true;
    }
    s3d::String EnvParser::interp(const s3d::String& s)
    {
        String result;
        size_t start = 0;
        size_t pos = 0;
        size_t length = s.length();
        while (pos < length && pos != String::npos) {
            if (auto b = s.indexOf(U"${", start); b != String::npos) {
                if (auto e = s.indexOf(U'}', b); e != String::npos) {
                    auto replace = s.substr(b + 2, e - (b + 2));
                    if (IsKeyName(replace)) {
                        result += s.substr(start, b - start);
                        result += this->get(replace);
                        start = pos = e;
                        ++start;
                    }
                }
            }
            ++pos;
        }
        result += s.substr(start, pos - start);

        return result;
    }
    s3d::String EnvParser::parseValue(const s3d::String& s)
    {
        size_t pos = 0;
        size_t length = s.length();

        if (s[0] == U'"') {
            ++pos;
            const size_t start = pos;
            while (pos < length) {
                if (s[pos] == U'\"' && s[pos - 1] != U'\\') {
                    break;
                }
                ++pos;
            }
            auto removedQuote = s.substr(start, pos - start).replace(U"\\\"", U"\"");
            return this->interp(std::move(removedQuote));
        } else if (s[0] == U'\'') {
            ++pos;
            const size_t start = pos;
            while (pos < length) {
                if (s[pos] == U'\'' && s[pos - 1] != U'\\') {
                    break;
                }
                ++pos;
            }
            return s.substr(start, pos - start).replace(U"\\'", U"'");
        }
        return this->interp(RemoveComment(s));
    }
}
