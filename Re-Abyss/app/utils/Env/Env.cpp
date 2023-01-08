#include <abyss/utils/Env/Env.hpp>
#include <cstdlib>

namespace 
{
    enum MultilineType
    {
        SingleQuote = 1,
        DoubleQuote = 2,
    };
#ifdef _MSC_VER
    int setenv(const char* name, const char* value, int overwrite)
    {
        int errcode = 0;
        if (!overwrite) {
            size_t envsize = 0;
            errcode = getenv_s(&envsize, NULL, 0, name);
            if (errcode || envsize) return errcode;
        }
        return _putenv_s(name, value);
    }
#endif

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
    // 補完
    s3d::String Interp(const s3d::String& s)
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
                        result += abyss::Env::Get(replace);
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
    s3d::String ParseValue(const s3d::String& s)
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
            return Interp(std::move(removedQuote));
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
        return Interp(RemoveComment(s));
    }
}
namespace abyss
{
    bool Env::Set(const s3d::String& key, const s3d::String& value, bool overwrite)
    {
        using namespace std;
        return setenv(key.narrow().c_str(), value.narrow().c_str(), overwrite) == 0;
    }
    s3d::String Env::Get(const s3d::String& key)
    {
        return GetOpt(key).value();
    }
    s3d::Optional<s3d::String> Env::GetOpt(const s3d::String& key)
    {
        std::string value;
#ifdef _MSC_VER
        char* buf = nullptr;
        size_t size = 0;
        if (_dupenv_s(&buf, &size, key.narrow().c_str()) == 0) {
            if (buf) {
                value = buf;
                free(buf);
            }
        }
#else
        value = std::getenv(key.narrow().c_str());
#endif
        if (value.empty()) {
            return s3d::none;
        }
        return s3d::Unicode::FromUTF8(value);
    }
    bool Env::Load(const s3d::String& path, bool overwrite)
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
                        value += ::Interp(line.replaced(U"\\\"", U"\""));
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
                    value = ::ParseValue(v);
                }
            }
            if (multiLine > 0) {
                // マルチライン中
                continue;
            }
            // 環境設定更新
            Env::Set(key, value, overwrite);
        }
        return true;
    }
}
