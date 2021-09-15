#pragma once
#include <Siv3D/Color.hpp>
#include <Siv3D/Periodic.hpp>

namespace abyss::ColorDef
{
    inline s3d::ColorF OnDamage(double time)
    {
        double rate = s3d::Periodic::Triangle0_1(0.3, time);
        double gb = s3d::Math::Lerp(1.0, 0.5, rate);
        return s3d::ColorF(1.0, gb, gb, 1.0);
    }
    inline s3d::ColorF OnDamage(bool isDamaging, double time, const s3d::ColorF& defaultColor = s3d::Palette::White)
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