#include "PlayerShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include "PlayerShotEffect.hpp"
namespace abyss
{
    PlayerShotVM::PlayerShotVM(const PlayerShotModel& shot, Forward forward):
        m_texture(U"resources/images/actors/Player/player_shot.png"),
        m_shot(shot),
        m_forward(forward)
    {}

    PlayerShotVM& PlayerShotVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    void PlayerShotVM::addShotFiringEffect()
    {
        if (!m_shot.isNormal()) {
            ActionSystem::World()->addEffect<PlayerShotFiringEffect>(m_pos, m_shot.toRadius(), m_shot.toColorF());
        }
    }
    void PlayerShotVM::draw()
    {
        double r = m_shot.toRadius();

        // effect
        if (Scene::FrameCount() % 2 && m_shot > PlayerShotType::Medium) {
            ActionSystem::World()->addEffect<PlayerShotEffect>(m_pos, r, m_shot.toColorF());
        }

        double x = 0, y = 0;
        double size = 0;
        double timer = Periodic::Sawtooth0_1(0.3s);
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

        ActionSystem::Light()->addLight({ m_pos, r * 5 });
    }
}
