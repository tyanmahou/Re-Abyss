#include "BaseState.hpp"

#include <abyss/controllers/System/System.hpp>

namespace abyss::Schield::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
    }

    void BaseState::start()
    {

    }
}
