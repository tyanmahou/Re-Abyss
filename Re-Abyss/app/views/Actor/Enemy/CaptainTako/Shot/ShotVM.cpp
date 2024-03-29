#include <abyss/views/Actor/Enemy/CaptainTako/Shot/ShotVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    ShotVM::ShotVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Common/EnemyShot.json"))
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
        tile.mirrored(m_forward.isRight()).drawAt(m_pos);
    }
}
