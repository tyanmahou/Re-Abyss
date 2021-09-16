#include "FootVM.hpp"
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
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
        m_pos = s3d::Round(pos);
        return *this;
    }
    FootVM& FootVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void FootVM::draw() const
    {
        auto color = ColorDef::OnDamage(m_isDamaging, m_time);

        // 足
        auto page = static_cast<s3d::int32>(s3d::Periodic::Sine0_1(5.0, m_time) * 6) % 6;
        auto rate = s3d::Periodic::Sine0_1(5.0, m_time);
        auto offset = s3d::Math::Lerp(-0.01, 0.01, rate);
        m_texture(U"foot")(page % 2 * 300, page / 2 * 180).scaled(1.0 + offset).drawAt(m_pos, color);
    }
}
