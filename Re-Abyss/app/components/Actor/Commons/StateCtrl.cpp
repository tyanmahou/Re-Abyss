#include "StateCtrl.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/base/IStateCallback.hpp>

namespace abyss::Actor
{
    void IState::init(StateCtrl* manager)
    {
        m_manager = manager;
        m_pActor = manager->getActor();
        this->setup();
    }

    StateCtrl::StateCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void StateCtrl::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<IStateCallback>();
    }

    void StateCtrl::onStart()
    {
        this->stateUpdate();
    }

    void StateCtrl::onEnd()
    {
        if (m_current) {
            m_current->end();
        }
    }

    void StateCtrl::stateUpdate()
    {
        if (m_next.second) {
            if (m_current) {
                m_current->end();
            }
            m_current = m_next.second;
            m_collisionReact = std::dynamic_pointer_cast<IPostCollision>(m_current);
            m_task = std::make_unique<Coro::Task<void>>(m_current->task());
            m_current->init(this);
            m_next.first = 0;
            m_next.second = nullptr;
            m_doneOnStart = false;
            // コールバックを呼ぶ
            for (auto&& callback : m_pActor->finds<IStateCallback>()) {
                callback->onStateStart();
            }
        }
    }

    void StateCtrl::onPostUpdate()
    {
        this->stateUpdate();
        if (!m_doneOnStart && m_current) {
            m_current->start();
            m_doneOnStart = true;
        }
        if (m_task) {
            m_task->moveNext();
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