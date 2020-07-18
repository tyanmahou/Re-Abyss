#include "StateModel.hpp"

namespace abyss
{
    void IState::init(StateModel* manager)
    {
        m_manager = manager;
        m_pActor = manager->getActor();
        this->setup();
        this->start();
    }
}