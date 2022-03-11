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
    s3d::ColorF Invincible(double time, double rate)
    {
        double r = s3d::Periodic::Triangle0_1(0.125, time);
        rate = s3d::EaseOutQuad(rate);
        double rgb = s3d::Math::Lerp(s3d::Math::Lerp(0.4, 0.0, rate), 0, r);
        return s3d::ColorF(rgb, 0.0);
    }
    s3d::ColorF Invincible(bool isInvincible, double time, double rate, const s3d::ColorF& defaultColor)
    {
        if (!isInvincible) {
            return defaultColor;
        }
        return Invincible(time, rate);
    }
}