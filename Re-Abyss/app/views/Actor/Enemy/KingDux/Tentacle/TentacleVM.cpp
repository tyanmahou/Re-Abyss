#include "TentacleVM.hpp"
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    TentacleVM::TentacleVM() :
        m_texture(Resource::Assets::Main()->load(U"actors/Enemy/KingDux/king_dux.json"))
    {}

    TentacleVM& TentacleVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }

    TentacleVM& TentacleVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    TentacleVM& TentacleVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }

    TentacleVM& TentacleVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void TentacleVM::draw() const
    {
        const auto color = ColorDef::OnDamage(m_isDamaging, m_time);
        auto scaleRate = s3d::Periodic::Triangle0_1(2.0, m_time);
        auto scale = 1.0 + s3d::Math::Lerp(0.0, 0.1, scaleRate);
        m_texture(U"tentacle")
            .scaled(scale)
            .rotated(m_rotate)
            .drawAt(m_pos, color);
    }
}