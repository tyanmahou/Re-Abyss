#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/PursuitState.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/Builder.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void WaitState::start()
    {
        using namespace Effect::Actor::Enemy::CodeZero;

        m_scale->setTo(1.0, ShotParam::Wait::ScaleTime);
        m_pActor
            ->getModule<Effects>()
            ->createWorldFront<ShotCharge::Builder>(m_body->getPos());

        m_quake = m_pActor
            ->getModule<Camera>()
            ->startQuake(1.0);
    }

    void WaitState::end()
    {
        if (m_quake) {
            m_quake->stop();
        }
    }

    void WaitState::update()
    {
        auto dt = m_pActor->deltaTime();
        m_scale->update(dt);

        if (m_scale->get() >= 1.0) {
            this->changeState<PursuitState>();
        }
    }
}

