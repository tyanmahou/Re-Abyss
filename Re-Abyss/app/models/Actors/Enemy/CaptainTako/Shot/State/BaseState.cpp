#include "BaseState.hpp"

#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

namespace abyss::CaptainTako::Shot
{
    void BaseState::setup()
    {
    }

    void BaseState::start()
    {
        this->m_pActor->find<AudioSourceModel>()->playAt(U"Shot");
    }

}
