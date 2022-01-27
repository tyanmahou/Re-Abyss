#include <abyss/views/Actor/Enemy/RollingTako/RollingTakoVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/params/Actor/Enemy/RollingTako/Param.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    RollingTakoVM::RollingTakoVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/RollingTako/RollingTako.png"))
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
    void RollingTakoVM::draw() const
    {
        switch (m_motion) {
        case Motion::Wait:
            this->drawWait();
            break;
        case Motion::Run:
            this->drawRun();
            break;
        default:
            break;
        }
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