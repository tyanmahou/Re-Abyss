#include "WaitState.hpp"
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/ActionSystem/ActManager.hpp>
#include <abyss/views/Actors/CodeZero/Shot/ShotChargeEffect.hpp>
#include <abyss/views/Actors/CodeZero/Shot/ShotVM.hpp>
#include <abyss/params/Actors/CodeZero/ShotParam.hpp>
namespace abyss::CodeZero::Shot
{
    void WaitState::start()
    {
        m_scale->setTo(1.0, ShotParam::Wait::ScaleTime);
        m_actor
            ->getModule<World>()
            ->addEffect<ShotChargeEffect>(m_body->getPos());
    }

    void WaitState::update(double dt)
    {
        m_scale->update(dt);

        if (m_scale->get() >= 1.0) {
            this->changeState(State::Pursuit);
        }
    }
    void WaitState::draw() const
    {
        auto view = m_actor->getBindedView();
        view->drawCharge();
        view->draw();
    }
}

