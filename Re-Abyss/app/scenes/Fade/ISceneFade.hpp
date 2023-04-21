#pragma once
#include <Siv3D/RectF.hpp>

namespace abyss::Fade
{
    class ISceneFade
    {
    public:
        virtual ~ISceneFade() = default;
        virtual void onFade(const s3d::RectF& rect, double t) const = 0;
    };
}
