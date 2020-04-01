#include "SlimeVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    // todo flyweightのいい感じにする
    static Texture Get()
    {
        static Texture tex(U"resources/images/actors/Slime/slime.png");
        return tex;
    }
    SlimeVM::SlimeVM():
        m_texture(Get())
    {}
    SlimeVM& SlimeVM::setForward(const Forward & forward)
    {
        m_forward = forward;
        return *this;
    }
    SlimeVM& SlimeVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = Math::Ceil(pos);
        return *this;
    }
    SlimeVM& SlimeVM::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        return *this;
    }

    SlimeVM& SlimeVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void SlimeVM::drawWalk() const
    {
        bool isLeft = m_forward == Forward::Left;
        int32 time = static_cast<int32>(Periodic::Square0_1(1s, WorldTime::Time()));
        auto tex = m_texture(40 * time, 0, 40, 40);
        (isLeft ? tex : tex.mirrored()).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }

    void SlimeVM::drawJump() const
    {
        bool isLeft = m_forward == Forward::Left;

        int32 page = m_velocity.y > 0 ? 1 : 0;
        auto tex = m_texture(40 * page, 40, 40, 40);
        (isLeft ? tex : tex.mirrored()).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }

}
