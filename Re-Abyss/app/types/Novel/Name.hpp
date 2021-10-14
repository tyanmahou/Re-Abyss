#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Novel
{
    class Name
    {
    public:
        Name() = default;
        Name(const s3d::Optional<s3d::String>& name):
            m_name(name)
        {}
        Name(const s3d::String& name) :
            m_name(name)
        {}
        Name(s3d::None_t) :
            m_name(s3d::none)
        {}
    private:
        s3d::Optional<s3d::String> m_name;
    };
}