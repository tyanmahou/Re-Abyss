#include "EffectCtrl.hpp"
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/views/Actor/Player/Shot/ShotEffect.hpp>
#include <abyss/components/Effect/Misc/ShockWaveDist/Builder.hpp>

namespace abyss::Actor::Player::Shot
{
    using namespace abyss::Effect::Misc;

    EffectCtrl::EffectCtrl(ActorObj* pActor):
        m_pActor(pActor)
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
                m_pActor->getModule<Effects>()->createWorldFront<ShockWaveDist::Builder>(
                    pos,
                    r * r / 2.0
                    );
            }
        }
    }

    void EffectCtrl::onPreDraw()
    {
        if (*m_shot >= PlayerShotType::Medium) {

            s3d::Vec2 pos = m_body->getPos();
            double radius = m_shot->toRadius();
            auto* pLight = m_pActor->getModule<Light>();

            // Effect
            for ([[maybe_unused]] double carryOver : m_effectTimer.update(m_pActor->deltaTime())) {
                m_pActor->getModule<Effects>()->createWorldFront<ShotEffect>(pos, radius, m_shot->toColorF(), pLight);
                m_pActor->getModule<Effects>()->createWorldFront<ShockWaveDist::Builder>(
                    pos,
                    radius * std::sqrt(radius) / 2.0,
                    10
                    )->setTimeScale(2.0);
            }
        }
    }

    void EffectCtrl::onDraw() const
    {
        s3d::Vec2 pos = m_body->getPos();
        double radius = m_shot->toRadius();

        auto* pLight = m_pActor->getModule<Light>();
        pLight->addCircle(pos, radius * 2.5);
    }
}
