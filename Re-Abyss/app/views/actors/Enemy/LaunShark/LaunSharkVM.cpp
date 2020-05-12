#include "LaunSharkVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/Param.hpp>
namespace abyss::LaunShark
{
    LaunSharkVM::LaunSharkVM():
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Enemy/LaunShark/laun_shark.json"))
    {}
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
    void LaunSharkVM::drawSwim() const
    {
        bool isRight = m_forward == Forward::Right;
        int32 time = static_cast<int32>(Periodic::Square0_1(Param::View::SwimAnimeTimeSec, WorldTime::Time()));
        m_texture(U"wait")({ 0, 60 * time }, { 120, 60 }).mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
    void LaunSharkVM::drawAttack() const
    {
        bool isRight = m_forward == Forward::Right;

        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(Param::View::AttackAnimeTimeSec, WorldTime::Time()) * 8);
        m_texture(U"attack")({ 120 * (page / 4), 80 * (page %  4) }, { 120, 80 }).mirrored(isRight).drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
    void LaunSharkVM::drawLauncher(double launcherTime) const
    {
        auto tex = m_texture(U"launcher");
        bool isRight = m_forward == Forward::Right;
        int32 page = static_cast<int32>(Periodic::Square0_1(1s, WorldTime::Time()));

        auto color = ColorDef::OnDamage(m_isDamaging, WorldTime::Time());
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
