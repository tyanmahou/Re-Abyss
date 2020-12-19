#include "WaitState.hpp"
#include "PursuitState.hpp"
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Shot/ShotChargeEffect.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    Task<> WaitState::start()
    {
        m_scale->setTo(1.0, ShotParam::Wait::ScaleTime);
        m_pActor
            ->getModule<Effects>()
            ->addWorldFront<ShotChargeEffect>(m_pActor->getModule<GlobalTime>(), m_body->getPos());
        co_return;
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

