#include <abyss/components/Actor/Player/ForwardCtrl.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>

namespace abyss::Actor::Player
{
    ForwardCtrl::ForwardCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void ForwardCtrl::setup(Executer executer)
    {
        executer.on<IMove>().addBefore<BodyUpdater>();
    }

    void ForwardCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void ForwardCtrl::onMove()
    {
        if (!m_isActive) {
            return;
        }
        const bool rightPressed = InputManager::Right.pressed();
        const bool leftPressed = InputManager::Left.pressed();
        if (rightPressed) {
            m_body->setForward(Forward::Right);
        } else if (leftPressed) {
            m_body->setForward(Forward::Left);
        }
    }

    void ForwardCtrl::onStateStart()
    {
        m_isActive = false;
    }
}