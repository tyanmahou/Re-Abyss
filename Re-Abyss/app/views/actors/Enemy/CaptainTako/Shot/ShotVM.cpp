#include "ShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::CaptainTako::Shot
{
    ShotVM::ShotVM():
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Common/enemy_shot.json"))
    {}
    ShotVM& ShotVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    ShotVM& ShotVM::setForward(const Forward & forward)
    {
        m_forward = forward;
        return *this;
    }
    ShotVM& ShotVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void ShotVM::draw() const
    {
        double timer = Periodic::Sawtooth0_1(0.3s, m_time);
        int32 page = static_cast<int32>(timer * 2);
        auto tile = m_texture(U"shot_e10x10")(0, page * 10, 10, 10);
        tile.mirrored(m_forward == Forward::Right).drawAt(m_pos);
    }
}
