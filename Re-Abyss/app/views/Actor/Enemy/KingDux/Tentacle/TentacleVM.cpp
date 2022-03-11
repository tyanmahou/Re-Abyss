#include <abyss/views/Actor/Enemy/KingDux/Tentacle/TentacleVM.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    TentacleVM::TentacleVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/KingDux/Tentacle.png"))
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
    TentacleVM& TentacleVM::setInvincibleColor(const s3d::ColorF color)
    {
        m_invincibleColor = color;
        return *this;
    }
    void TentacleVM::draw() const
    {
        const auto color = ColorDef::OnDamage(m_isDamaging, m_time);
        s3d::ScopedColorAdd2D addColor(m_invincibleColor);

        auto scaleRate = s3d::Periodic::Triangle0_1(2.0, m_time);
        auto scale = 1.0 + s3d::Math::Lerp(0.0, 0.01, scaleRate);

        m_texture
            .scaled(scale)
            .rotatedAt(TentacleParam::Base::RotPivot * scale , m_rotate)
            .drawAt(m_pos, color);
    }
}