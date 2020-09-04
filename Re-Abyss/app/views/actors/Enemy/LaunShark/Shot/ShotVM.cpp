#include "ShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ColorDef.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>
namespace abyss::Actor::Enemy::LaunShark::Shot
{
    ShotVM::ShotVM():
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Enemy/LaunShark/laun_shark.json"))
    {}
    ShotVM& ShotVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    ShotVM& ShotVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    ShotVM& ShotVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    ShotVM& ShotVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void ShotVM::draw(double t) const
    {
        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(ShotParam::View::AnimeTimeSec, t) * 4);
        m_texture(U"shark_shot")({ 0, 12 * page }, { 32, 12 })
            .rotated(m_rotate)
            .drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, m_time));
    }
    void ShotVM::drawWait() const
    {
        this->draw(0.0);
    }

    void ShotVM::drawFiringed() const
    {
        this->draw(m_time);
    }
}
