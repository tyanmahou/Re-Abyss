#pragma once
#include <Siv3D/Color.hpp>
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Palette.hpp>
#include <Siv3D/ScopedColorAdd2D.hpp>

namespace abyss::ColorDef
{
    s3d::ColorF OnDamage(double time);
    s3d::ColorF OnDamage(bool isDamaging, double time, const s3d::ColorF& defaultColor = s3d::Palette::White);

    s3d::ColorF Invincible(double time, double rate);
    s3d::ColorF Invincible(bool isInvincible, double time, double rate, const s3d::ColorF& defaultColor = s3d::ColorF(0, 0));

    namespace Shot
    {
        inline constexpr s3d::ColorF BigCharge{ 1.0, 1.0, 0.0 };
        inline constexpr s3d::ColorF MediumCharge{ 0.5, 0.5, 1.0 };
        inline constexpr s3d::ColorF NormalCharge{ 1.0 };
    }
}