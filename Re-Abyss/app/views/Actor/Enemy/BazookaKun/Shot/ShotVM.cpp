#include <abyss/views/Actor/Enemy/BazookaKun/Shot/ShotVM.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/ShotParam.hpp>

namespace abyss::Actor::Enemy::BazookaKun::Shot
{
    ShotVM::ShotVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Common/EnemyShot.json"))
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

    void ShotVM::draw() const
    {
        double timer = Periodic::Sawtooth0_1(ShotParam::View::AnimeTimeSec, m_time);
        int32 page = static_cast<int32>(timer * 2);
        auto tile = m_texture(U"shot_c9")(0, page * 9, 9, 9);
        tile.rotated(s3d::Math::ToRadians(ShotParam::View::RotateDeg) * m_time).drawAt(m_pos);
    }

}
