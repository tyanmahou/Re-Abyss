#include <abyss/views/Actor/Enemy/LaunShark/Shot/ShotVM.hpp>

#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    ShotVM::ShotVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/LaunShark/LaunShark.json"))
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
    ShotVM& ShotVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    void ShotVM::draw() const
    {
        switch (m_motion) {
        case Motion::Wait:
            return this->drawWait();
        case Motion::Firinged:
            return this->drawFiringed();
        default:
            break;
        }
    }
    void ShotVM::drawBase(double t) const
    {
        int32 page = static_cast<int32>(Periodic::Sawtooth0_1(ShotParam::View::AnimeTimeSec, t) * 4);
        m_texture(U"shark_shot")({ 0, 12 * page }, { 32, 12 })
            .rotated(m_rotate)
            .drawAt(m_pos, m_colorMul);
    }
    void ShotVM::drawWait() const
    {
        this->drawBase(0.0);
    }

    void ShotVM::drawFiringed() const
    {
        this->drawBase(m_time);
    }
}
