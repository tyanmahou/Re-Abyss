#pragma once
#include <Siv3D/Color.hpp>

namespace abyss::ColorDef
{
    inline constexpr s3d::ColorF OnDamage(double time)
    {
        return static_cast<s3d::int32>(time * 10.0) % 2 ? s3d::ColorF(1.0, 0.5, 0.5, 0.5) : s3d::ColorF(1.0);
    }
    inline constexpr s3d::ColorF OnDamage(bool isDamaging, double time, const s3d::ColorF& defaultColor = s3d::Palette::White)
    {
        if (!isDamaging) {
            return defaultColor;
        }
        return OnDamage(time);
    }

    namespace Shot
    {
        inline constexpr s3d::ColorF BigCharge{ 1.0, 1.0, 0.0 };
        inline constexpr s3d::ColorF MediumCharge{ 0.5, 0.5, 1.0 };
        inline constexpr s3d::ColorF NormalCharge{ 1.0 };
    }
}