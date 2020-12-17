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

    StateCtrl::StateCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void StateCtrl::setup(Depends depends)
    {
        depends.addAfter<IComponent>();
    }

    void StateCtrl::onStart()
    {
        this->stateUpdate();
    }

    void StateCtrl::stateUpdate()
    {
        if (m_next) {
            if (m_current) {
                m_current->end();
            }
            m_current = m_next;
            m_collisionReact = std::dynamic_pointer_cast<ICollisionReact>(m_current);
            m_current->init(this);
            m_next = nullptr;
        }
    }

    void StateCtrl::onUpdate()
    {
        this->stateUpdate();
        if (m_current) {
            m_current->update();
        }
    }
    void StateCtrl::onLastUpdate()
    {
        if (m_current) {
            m_current->lastUpdate();
        }
    }

    void StateCtrl::onDraw() const
    {
        if (m_current) {
            m_current->draw();
        }
    }

    void StateCtrl::onCollisionReact()
    {
        if (m_collisionReact) {
            m_collisionReact->onCollisionReact();
        }
    }

    void StateCtrl::changeState(const std::shared_ptr<IState>& next)
    {
        m_next = next;
    }


}