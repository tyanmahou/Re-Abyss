#include "SchieldShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/params/Actors/Schield/SchieldShotParam.hpp>

namespace abyss
{
    SchieldShotVM::SchieldShotVM() :
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Common/enemy_shot.json"))
    {}

    SchieldShotVM& SchieldShotVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    void SchieldShotVM::draw() const
    {
        double t = WorldTime::Time();
        double timer = Periodic::Sawtooth0_1(SchieldShotParam::View::AnimeTimeSec, t);
        int32 page = static_cast<int32>(timer * 2);
        auto tile = m_texture(U"shot_c9")(0, page * 9, 9, 9);
        tile.rotated(s3d::Math::ToRadians(SchieldShotParam::View::RotateDeg) * t).drawAt(m_pos);
    }

}
