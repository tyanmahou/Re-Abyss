#include <abyss/commons/ColorDef.hpp>
#include <Siv3D.hpp>

namespace abyss::ColorDef
{
    s3d::ColorF OnDamage(double time)
    {
        double rate = s3d::Periodic::Triangle0_1(0.3, time);
        double gb = s3d::Math::Lerp(1.0, 0.5, rate);
        return s3d::ColorF(1.0, gb, gb, 1.0);
    }
    s3d::ColorF OnDamage(bool isDamaging, double time, const s3d::ColorF& defaultColor)
    {
        if (!isDamaging) {
            return defaultColor;
        }
        return OnDamage(time);
    }
    s3d::ColorF Invincible(double time)
    {
        double rate = s3d::Periodic::Triangle0_1(0.15, time);
        double rgb = s3d::Math::Lerp(0.0, 0.2, rate);
        return s3d::ColorF(rgb, 0.0);
    }
    s3d::ColorF Invincible(bool isInvincible, double time, const s3d::ColorF& defaultColor)
    {
        if (!isInvincible) {
            return defaultColor;
        }
        return Invincible(time);
    }
}