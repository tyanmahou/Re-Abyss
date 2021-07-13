#include "EffectCtrl.hpp"
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/views/Actor/Player/Shot/ShotEffect.hpp>
#include <abyss/views/Actor/Common/ShockWaveDist.hpp>

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
            const s3d::Vec2& pos = m_body->getPos();
            double r = m_shot->toRadius();
            m_pActor->getModule<Effects>()->createWorldFront<ShotFiringEffect>(
                pos,
                r,
                m_shot->toColorF()
                );
            if (!m_shot->isSmall()) {
                m_pActor->getModule<Effects>()->createWorldFront<ShockWaveDist>(
                    m_pActor->getManager(),
                    pos,
                    r * r / 2.0
                    );
            }
        }
    }

    void EffectCtrl::onDraw() const
    {
        s3d::Vec2 pos = m_body->getPos();
        double radius = m_shot->toRadius();

        auto* pLight = m_pActor->getModule<Light>();
        // effect
        if (m_effectTimer.update() && *m_shot >= PlayerShotType::Medium) {
            m_pActor->getModule<Effects>()->createWorldFront<ShotEffect>(pos, radius, m_shot->toColorF(), pLight);
            m_pActor->getModule<Effects>()->createWorldFront<ShockWaveDist>(
                m_pActor->getManager(),
                pos,
                radius * std::sqrt(radius) / 2.0,
                10,
                2.0
                );
        }
        pLight->addCircle(pos, radius * 2.5);
    }
}
