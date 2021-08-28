#include "ShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Player::Shot
{
    ShotVM::ShotVM(const PlayerShot& shot, Forward forward):
        m_texture(Resource::Assets::Main()->load(U"actors/Player/player_shot.png")),
        m_shot(shot),
        m_forward(forward)
    {}

    ShotVM& ShotVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    ShotVM& ShotVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void ShotVM::draw()
    {
        double x = 0, y = 0;
        double size = 0;
        double timer = Periodic::Sawtooth0_1(0.3s, m_time);
        if (m_shot.isNormal()) {
            y = 10 * static_cast<int>(timer * 2);
            size = 10;
        } else if (m_shot.isSmall()) {
            x = 10;
            y = 20 * static_cast<int>(timer * 2);
            size = 20;
        } else if (m_shot.isMedium()) {
            x = 30 + 40 * static_cast<int>(timer * 4);
            size = 40;
        } else {
            x = 60 * static_cast<int>(timer * 4);
            y = 40;
            size = 60;
        }
        auto tile = m_texture(x, y, size, size);
        (m_forward == Forward::Right ? tile : tile.mirrored()).drawAt(m_pos);
    }
}
