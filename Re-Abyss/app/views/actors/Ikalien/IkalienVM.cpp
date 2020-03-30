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
        m_pos = pos;
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
        int32 page = static_cast<int32>(Periodic::Sine0_1(1.5s, t) * 4.0);
        auto tex = m_texture(80 * page, 0, 80, 80);
        tex.rotated(m_rotate).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, t));
    }

}
