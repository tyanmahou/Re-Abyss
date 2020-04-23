#include "ShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::CodeZero::Shot
{
    ShotVM::ShotVM() :
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/CodeZero/code_zero.json"))
    {}
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
        double time = WorldTime::Time();
        auto tmp = static_cast<s3d::int32>(time * 10.0);
        double alpha = tmp % 2 ? 0.9 : 0.5;
        if (tmp % 20 == 0) {
            alpha = 0.0f;
        }
        m_texture(U"shot")
            .mirrored(tmp%2==0)
            .fliped(tmp%3==0)
            .scaled(m_scale + 0.2 * (tmp % 7 == 0))
            .drawAt(m_pos, ColorF(1.0, alpha));
    }
    void ShotVM::drawCharge() const
    {
        double time = WorldTime::Time();
        auto tmp = static_cast<s3d::int32>(time * 10.0);
        double alpha = tmp % 2 ? 0.9 : 0.5;
        if (tmp % 20 == 0) {
            alpha = 0.0f;
        }

        Circle(m_pos, 150 * (1 - Periodic::Sawtooth0_1(0.6s, time)))
            .drawFrame(1, 1, ColorF(0.0, alpha));
    }
}
