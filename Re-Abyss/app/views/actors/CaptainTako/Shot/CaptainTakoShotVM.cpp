#include "CaptainTakoShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    CaptainTakoShotVM::CaptainTakoShotVM():
        m_texture(U"resources/images/actors/CaptainTako/tako_shot.png")
    {}
    CaptainTakoShotVM& CaptainTakoShotVM::setForward(const Forward & forward)
    {
        m_forward = forward;
        return *this;
    }
    CaptainTakoShotVM& CaptainTakoShotVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void CaptainTakoShotVM::draw() const
    {
        double timer = Periodic::Sawtooth0_1(0.3s, WorldTime::Time());
        int32 page = static_cast<int32>(timer * 2);
        auto tile = m_texture(0, page, 10, 10);
        tile.mirrored(m_forward == Forward::Right).drawAt(m_pos);
    }
}
