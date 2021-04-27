#include "ShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    ShotVM::ShotVM() :
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"actors/Enemy/CodeZero/code_zero.json"))
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
    ShotVM& ShotVM::setScale(double scale)
    {
        m_scale = scale;
        return *this;
    }
    void ShotVM::draw() const
    {
        auto tmp = static_cast<s3d::int32>(m_time * 10.0);
        double alpha = tmp % 2 ? 0.9 : 0.5;
        if (tmp % 20 == 0) {
            alpha = 0.0f;
        }
        m_texture(U"shot")
            .mirrored(tmp%2==0)
            .flipped(tmp%3==0)
            .scaled(m_scale + 0.2 * (tmp % 7 == 0))
            .drawAt(m_pos, ColorF(1.0, alpha));
    }
    void ShotVM::drawCharge() const
    {
        auto tmp = static_cast<s3d::int32>(m_time * 10.0);
        double alpha = tmp % 2 ? 0.9 : 0.5;
        if (tmp % 20 == 0) {
            alpha = 0.0f;
        }

        Circle(m_pos, 150 * (1 - Periodic::Sawtooth0_1(0.6s, m_time)))
            .drawFrame(1, 1, ColorF(0.0, alpha));
    }
}