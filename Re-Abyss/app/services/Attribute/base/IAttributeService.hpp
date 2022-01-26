#pragma once
#include <Siv3D/Color.hpp>

namespace abyss::Attribute
{
    class IAttributeService
    {
    public:
        virtual ~IAttributeService() = default;

        virtual s3d::Color getBgColor() const = 0;
    };
}