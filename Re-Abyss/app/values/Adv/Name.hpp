#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::Adv
{
    class Name
    {
    public:
        Name() = default;
        Name(const s3d::Optional<s3d::String>& name):
            m_name(name)
        {}
        Name(const s3d::String::value_type* name) :
            m_name(name)
        {}
        Name(const s3d::String& name) :
            m_name(name)
        {}
        Name(s3d::None_t) :
            m_name(s3d::none)
        {}

        bool isNoname() const
        {
            return !m_name.has_value();
        }
        operator const s3d::Optional<s3d::String>& () const
        {
            return m_name;
        }
    private:
        s3d::Optional<s3d::String> m_name;
    };
}
