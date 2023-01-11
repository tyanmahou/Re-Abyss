#include <abyss/utils/Env/Env.hpp>
#include <abyss/utils/Env/detail/EnvParser.hpp>
#include <cstdlib>

namespace 
{
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

    class EnvContainer : public abyss::detail::IEnvContainer
    {
    public:
        EnvContainer() = default;
    private:
        bool set(const s3d::String& key, const s3d::String& value, bool overwrite) override
        {
            using namespace std;
            return setenv(key.narrow().c_str(), value.narrow().c_str(), overwrite) == 0;
        }
        s3d::Optional<s3d::String> getOpt(const s3d::String& key) const override
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
    };

    // パーサー
    abyss::detail::EnvParser g_parser(std::make_unique<EnvContainer>());
}
namespace abyss
{
    bool Env::Set(const s3d::String& key, const s3d::String& value, bool overwrite)
    {
        return g_parser.set(key, value, overwrite);
    }
    s3d::String Env::Get(const s3d::String& key)
    {
        return g_parser.get(key);
    }
    s3d::Optional<s3d::String> Env::GetOpt(const s3d::String& key)
    {
        return g_parser.getOpt(key);
    }
    bool Env::Load(const s3d::String& path, bool overwrite)
    {
        return g_parser.load(path, overwrite);
    }
}
