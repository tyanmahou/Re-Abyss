#include "StateCtrl.hpp"

namespace abyss::Actor
{
    void IState::init(StateCtrl* manager)
    {
        m_manager = manager;
        m_pActor = manager->getActor();
        this->setup();
    }

    StateCtrl::StateCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void StateCtrl::setup(Executer executer)
    {
        //executer.addAfter<IComponent>();
    }

    void StateCtrl::onStart()
    {
        this->stateUpdate();
    }

    void StateCtrl::stateUpdate()
    {
        if (m_next.second) {
            if (m_current) {
                m_current->end();
            }
            m_current = m_next.second;
            m_collisionReact = std::dynamic_pointer_cast<IPostCollision>(m_current);
            m_startTask = std::make_unique<Coro::Task<void>>(m_current->start());
            m_current->init(this);
            m_next.first = 0;
            m_next.second = nullptr;
        }
    }

    void StateCtrl::onPostUpdate()
    {
        this->stateUpdate();
        if (m_startTask) {
            m_startTask->moveNext();
        }
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

    void StateCtrl::onPostCollision()
    {
        if (m_collisionReact) {
            m_collisionReact->onPostCollision();
        }
    }

    void StateCtrl::changeState(const std::shared_ptr<IState>& next, StatePriorityType priority)
    {
        if (m_next.second && (m_next.first > priority)) {
            return;
        }
        m_next.first = priority;
        m_next.second = next;
    }


}