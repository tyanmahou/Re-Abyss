#include "StateCtrl.hpp"

namespace abyss::Actor
{
    void IState::init(StateCtrl* manager)
    {
        m_manager = manager;
        m_pActor = manager->getActor();
        this->setup();
        this->start();
    }
}