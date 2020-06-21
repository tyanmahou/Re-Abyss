#include "BaseState.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>

namespace abyss::Schield
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
    }
    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }
}
