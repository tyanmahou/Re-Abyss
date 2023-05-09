#pragma once
#include <Siv3D/Color.hpp>

namespace abyss::Fade
{
    class IFadeColor
    {
    public:
        virtual ~IFadeColor() = default;
        virtual void setColor(const s3d::ColorF& color) = 0;
    };
}
