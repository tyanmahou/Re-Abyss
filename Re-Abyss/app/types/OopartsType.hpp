#pragma once
#include <Siv3D/String.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
namespace abyss
{
    enum class OopartsType
    {
        Invalid,
        Xto,
        Nyan
    };
}

namespace abyss::Enum
{
    template<>
    struct EnumTraits<OopartsType>
    {
        OopartsType operator()(const s3d::String& value)
        {
            if (value == U"Invalid") {
                return OopartsType::Invalid;
            }
            if (value == U"Xto") {
                return OopartsType::Xto;
            }
            if (value == U"Nyan") {
                return OopartsType::Nyan;
            }
        }

        s3d::String operator()(OopartsType value)
        {
            if (value == OopartsType::Invalid) {
                return U"Invalid";
            }
            if (value == OopartsType::Xto) {
                return U"Xto";
            }
            if (value == OopartsType::Nyan) {
                return U"Nyan";
            }
        }
    };
}