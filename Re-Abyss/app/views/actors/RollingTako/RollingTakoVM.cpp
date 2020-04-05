#include "RollingTakoVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    RollingTakoVM::RollingTakoVM():
        m_texture(U"resources/images/actors/RollingTako/rolling_tako.png")
    {}
    RollingTakoVM& RollingTakoVM::setForward(const Forward & forward)
    {
        m_forward = forward;
        return *this;
    }
    RollingTakoVM& RollingTakoVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    RollingTakoVM& RollingTakoVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void RollingTakoVM::drawWait() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 time = static_cast<int32>(Periodic::Square0_1(1s, WorldTime::Time()));
        auto tex = m_texture(60 * time, 0, 60, 60);
        tex.mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
    void RollingTakoVM::drawRun() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 time = static_cast<int32>(Periodic::Square0_1(0.2s, WorldTime::Time()));
        auto tex = m_texture(60 * time, 60, 60, 60);
        tex.mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
}