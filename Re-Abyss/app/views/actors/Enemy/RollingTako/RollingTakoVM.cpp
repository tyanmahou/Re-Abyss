#include "RollingTakoVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
namespace abyss::RollingTako
{
    RollingTakoVM::RollingTakoVM():
        m_texture(ResourceManager::Main()->loadTexture(U"actors/Enemy/RollingTako/rolling_tako.png"))
    {}
    RollingTakoVM& RollingTakoVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
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
        int32 time = static_cast<int32>(Periodic::Square0_1(Param::View::WaitAnimeTimeSec, m_time));
        auto tex = m_texture(60 * time, 0, 60, 60);
        tex.mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
    void RollingTakoVM::drawRun() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 time = static_cast<int32>(Periodic::Square0_1(Param::View::RunAnimeTimeSec, m_time));
        auto tex = m_texture(60 * time, 60, 60, 60);
        tex.mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
}