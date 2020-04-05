#include "IkalienVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    IkalienVM::IkalienVM():
        m_texture(U"resources/images/actors/Ikalien/ikalien.png")
    {}
    IkalienVM& IkalienVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    IkalienVM& IkalienVM::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        return *this;
    }

    IkalienVM& IkalienVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }

    IkalienVM& IkalienVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }

    void IkalienVM::drawWait() const
    {
        double t = WorldTime::Time();
        int32 page = static_cast<int32>(Periodic::Triangle0_1(1.5s, t) * 4.0);
        auto tex = m_texture(80 * page, 80, 80, 80);
        tex.rotated(m_rotate).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, t));
    }

    void IkalienVM::drawPursuit() const
    {
        this->drawWait();
    }

    void IkalienVM::drawSwim() const
    {
        double t = WorldTime::Time();
        int32 page = 0;
        double velocityLen = m_velocity.length();
        if (velocityLen >= 300) {
            page = 3;
        } else if(velocityLen >= 280) {
            page = 2;
        } else if (velocityLen >= 260) {
            page = 1;
        }
        auto tex = m_texture(80 * page, 0, 80, 80);
        tex.rotated(m_rotate).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, t));
    }

}
