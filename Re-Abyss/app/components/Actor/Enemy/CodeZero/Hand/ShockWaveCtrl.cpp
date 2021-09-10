#include "ShockWaveCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandMove.hpp>
#include <abyss/components/Effect/Misc/ShockWaveDist/Builder.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    ShockWaveCtrl::ShockWaveCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_counter(0.033)
    {}
    void ShockWaveCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_handMove = m_pActor->find<HandMove>();
    }
    void ShockWaveCtrl::onPostCollision()
    {
        if (!m_isActive) {
            return;
        }
        using namespace abyss::Effect::Misc;
        const auto radius = HandParam::Base::ColRadius * 2.0;
        const auto& axis = m_handMove->getAxis();
        for ([[maybe_unused]] auto carryOver: m_counter.update(m_pActor->deltaTime())) {
            m_pActor->getModule<Effects>()->createWorldFront<ShockWaveDist::Builder>(
                m_body->getCenterPos() + axis * Vec2{50, 0},
                radius,
                20.0
                )->setTimeScale(2.0);
        }
    }
    void ShockWaveCtrl::onStateStart()
    {
        m_isActive = false;
    }
}
