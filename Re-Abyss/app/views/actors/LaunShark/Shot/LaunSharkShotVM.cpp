#include "LaunSharkShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace abyss
{
    LaunSharkShotVM::LaunSharkShotVM():
        m_texture(U"resources/images/actors/LaunShark/laun_shark.json")
    {}

    LaunSharkShotVM& LaunSharkShotVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Ceil(pos);
        return *this;
    }
    LaunSharkShotVM& LaunSharkShotVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    LaunSharkShotVM& LaunSharkShotVM::setIsDamaging(bool isDamaging)
    {
        m_isDamaging = isDamaging;
        return *this;
    }
    void LaunSharkShotVM::draw(double t) const
    {
        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(0.25s, t) * 4);
        m_texture(U"shark_shot")({ 0, 12 * page }, { 32, 12 })
            .rotated(m_rotate)
            .drawAt(m_pos, ColorDef::OnDamage(m_isDamaging, WorldTime::Time()));
    }
    void LaunSharkShotVM::drawWait() const
    {
        this->draw(0.0);
    }

    void LaunSharkShotVM::drawFiringed() const
    {
        this->draw(WorldTime::Time());
    }
}
