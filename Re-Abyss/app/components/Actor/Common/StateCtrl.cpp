#include <abyss/components/Actor/Common/StateCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>

namespace abyss::Actor
{
    void IState::init(StateCtrl* manager)
    {
        m_manager = manager;
        m_pActor = manager->getActor();
        this->onCache();
    }

    StateCtrl::StateCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void StateCtrl::setup(Executer executer)
    {
        executer.onStart().addAfter<IStateCallback>();
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
            m_task.reset(std::bind(&IState::updateAsync, m_current.get()));
            m_current->init(this);
            m_next.first = 0;
            m_next.second = nullptr;
            m_doneOnStart = false;
        }
    }

    void StateCtrl::onPreUpdate()
    {
        this->stateUpdate();
    }

    void StateCtrl::onPostUpdate()
    {
        this->stateUpdate();
        if (!m_doneOnStart && m_current) {
            // コールバックを呼ぶ
            for (auto&& callback : m_pActor->finds<IStateCallback>()) {
                callback->onStateStart();
            }
            m_current->start();
            m_doneOnStart = true;
        }
        m_task.resume();
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
