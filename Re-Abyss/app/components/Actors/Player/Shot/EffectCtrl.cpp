#include "EffectCtrl.hpp"
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Effects/Effects.hpp>
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/views/actors/Player/Shot/ShotEffect.hpp>

namespace abyss::Actor::Player::Shot
{
    EffectCtrl::EffectCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_effectTimer(0.033, true, pActor->getDrawClock())
    {}

    void EffectCtrl::setup([[maybe_unused]]Executer executer)
    {
    }

    void EffectCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_shot = m_pActor->find<PlayerShot>();
        if (!m_shot->isNormal()) {
            m_pActor->getModule<Effects>()->addWorldFront<ShotFiringEffect>(
                m_body->getPos(),
                m_shot->toRadius(),
                m_shot->toColorF()
                );
        }
    }

    void EffectCtrl::onDraw() const
    {
        Vec2 pos = m_body->getPos();
        double radius = m_shot->toRadius();

        auto* pLight = m_pActor->getModule<Light>();
        // effect
        if (m_effectTimer.update() && *m_shot >= PlayerShotType::Medium) {
            m_pActor->getModule<Effects>()->addWorldFront<ShotEffect>(pos, radius, m_shot->toColorF(), pLight);
        }
        pLight->addLight({ pos, radius * 5 });
    }
}
