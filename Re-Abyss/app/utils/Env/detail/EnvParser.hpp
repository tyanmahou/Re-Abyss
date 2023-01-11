#pragma once
#include <memory>
#include <Siv3D/Optional.hpp>
#include <Siv3D/String.hpp>

namespace abyss::detail
{
    class IEnvContainer
    {
    public:
        virtual ~IEnvContainer() = default;

        virtual bool set(const s3d::String& key, const s3d::String& value, bool overwrite) = 0;
        virtual s3d::Optional<s3d::String> getOpt(const s3d::String& key) const = 0;
    };

    class EnvParser
    {
    public:
        EnvParser(std::unique_ptr<IEnvContainer>&& container);

        bool set(const s3d::String& key, const s3d::String& value, bool overwrite = true);
        s3d::String get(const s3d::String& key) const;
        s3d::Optional<s3d::String> getOpt(const s3d::String& key) const;

        bool load(const s3d::String& path = U".env", bool overwrite = true);

    private:
        s3d::String interp(const s3d::String& s);
        s3d::String parseValue(const s3d::String& s);
    private:
        std::unique_ptr<IEnvContainer> m_container;
    };
}
