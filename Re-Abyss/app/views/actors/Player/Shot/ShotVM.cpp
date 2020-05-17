#include "ShotVM.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

#include "ShotEffect.hpp"
namespace abyss::Player::Shot
{
    ShotVM::ShotVM(const PlayerShotModel& shot, Forward forward):
        m_texture(ResourceManager::Main()->loadTexture(U"actors/Player/player_shot.png")),
        m_shot(shot),
        m_forward(forward)
    {}

    ShotVM& ShotVM::setManager(Manager * pManager)
    {
        m_pManager = pManager;
        return *this;
    }

    ShotVM& ShotVM::setPos(const s3d::Vec2 & pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }
    void ShotVM::addShotFiringEffect()
    {
        if (!m_shot.isNormal()) {
            m_pManager->getModule<World>()->addEffect<ShotFiringEffect>(m_pos, m_shot.toRadius(), m_shot.toColorF());
        }
    }
    void ShotVM::draw()
    {
        double r = m_shot.toRadius();

        // effect
        if (static_cast<int32>(Periodic::Sawtooth0_1(1s) * 60.0) % 2 && m_shot >= PlayerShotType::Medium) {
            m_pManager->getModule<World>()->addEffect<ShotEffect>(m_pos, r, m_shot.toColorF());
        }

        double x = 0, y = 0;
        double size = 0;
        double timer = Periodic::Sawtooth0_1(0.3s, WorldTime::Time());
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

        m_pManager->getModule<Light>()->addLight({ m_pos, r * 5 });
    }
}
