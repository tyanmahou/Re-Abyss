#include "LaunSharkVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/Param.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    LaunSharkVM::LaunSharkVM():
        m_texture(Resource::Assets::Main()->load(U"actors/Enemy/LaunShark/laun_shark.json"))
    {}
    LaunSharkVM& LaunSharkVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    LaunSharkVM& LaunSharkVM::setForward(const Forward& forward)
    {
        m_forward = forward;
        return *this;
    }
    LaunSharkVM& LaunSharkVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    LaunSharkVM& LaunSharkVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void LaunSharkVM::draw() const
    {
        switch (m_motion) {
        case Motion::Swim:
            return this->drawSwim();
        case Motion::Attack:
            return this->drawAttack();
        case Motion::Launcher:
            return this->drawLauncher(m_animeTime);
        default:
            break;
        }
    }
    void LaunSharkVM::drawSwim() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 time = static_cast<int32>(Periodic::Square0_1(Param::View::SwimAnimeTimeSec, m_time));
        m_texture(U"wait")({ 0, 60 * time }, { 120, 60 }).mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
    void LaunSharkVM::drawAttack() const
    {
        bool isRight = m_forward == Forward::Right;

        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(Param::View::AttackAnimeTimeSec, m_time) * 8);
        m_texture(U"attack")({ 120 * (page / 4), 80 * (page %  4) }, { 120, 80 }).mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
    void LaunSharkVM::drawLauncher(double launcherTime) const
    {
        auto tex = m_texture(U"launcher");
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, m_time));

        auto color = ColorDef::OnDamage(m_isDamaging, m_time);
        auto mousePos = m_pos + Vec2{ isRight ? 30 : -60, page == 1 ? -26 : -30};
        Vec2 lancherPos{
            mousePos.x + (isRight ? -50 : 50) * (1.0 - launcherTime),
            mousePos.y
        };
        tex({ 120, 60 }, { 30, 60 }).mirrored(isRight).draw(mousePos, color);
        tex({ 120, 0 }, { 30, 60 }).mirrored(isRight).draw(lancherPos, color);
        tex({ 0, 60 * page }, { 120, 60 }).mirrored(isRight).drawAt(m_pos, color);
    }
}
