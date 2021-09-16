#include "FootVM.hpp"
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Foot
{
    FootVM::FootVM() :
        m_texture(Resource::Assets::Main()->load(U"actors/Enemy/KingDux/king_dux.json"))
    {}
    FootVM& FootVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    FootVM& FootVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    FootVM& FootVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void FootVM::draw() const
    {
        const auto color = ColorDef::OnDamage(m_isDamaging, m_time);

        // 足
        const auto page = static_cast<s3d::int32>(s3d::Periodic::Triangle0_1(Param::Foot::AnimTimeSec, m_time) * 6) % 6;
        auto rate = s3d::Periodic::Triangle0_1(2.0, m_time);
        auto scale = 1.0 + s3d::Math::Lerp(0.0, 0.1, rate);
        constexpr auto size = s3d::Vec2{ 300, 180 };
        const auto scaledSize = size * scale;
        m_texture(U"foot")(page % 2 * 300, page / 2 * 180, size)
            .resized(scaledSize)
            .draw(s3d::Round(m_pos - scaledSize / 2.0), color);
    }
}
