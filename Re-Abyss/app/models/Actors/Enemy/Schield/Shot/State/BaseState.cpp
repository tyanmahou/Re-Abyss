#include "BaseState.hpp"

namespace abyss::Schield::Shot
{
    void BaseState::setup()
    {
        m_view = m_pActor->find<ViewModel<ShotVM>>().get();
    }

    void BaseState::start()
    {
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
