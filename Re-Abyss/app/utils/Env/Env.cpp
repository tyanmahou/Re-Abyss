#include "Env.hpp"
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
        return false;
    }
}
