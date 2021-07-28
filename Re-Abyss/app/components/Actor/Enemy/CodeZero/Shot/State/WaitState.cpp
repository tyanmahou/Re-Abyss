#include "WaitState.hpp"
#include "PursuitState.hpp"
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Shot/ShotChargeEffect.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/models/Camera/QuakeModel.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void WaitState::start()
    {
        m_scale->setTo(1.0, ShotParam::Wait::ScaleTime);
        m_pActor
            ->getModule<Effects>()
            ->createWorldFront<ShotChargeEffect>(m_pActor->getModule<GlobalTime>(), m_body->getPos());

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

    void WaitState::draw() const
    {
        if (auto view = m_view->getBindedView()) {
            view->drawCharge();
            view->draw();
        }
    }
}

