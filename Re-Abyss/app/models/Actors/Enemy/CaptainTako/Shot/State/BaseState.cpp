#include "BaseState.hpp"

#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/controllers/Actors/ActInclude.hpp>

namespace abyss::CaptainTako::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
    }

    void BaseState::start()
    {
        this->m_pActor->find<AudioSourceModel>()->playAt(U"Shot");
    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }
}
