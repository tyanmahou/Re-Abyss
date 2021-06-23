#include "PauseCtrl.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Event/GamePause/Builder.hpp>


namespace abyss::Actor::God
{
    PauseCtrl::PauseCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void PauseCtrl::onUpdate()
    {
        if (InputManager::Start.down()) {
            auto pEvent = m_pActor->getModule<Events>();
            if (pEvent->isEmpty()) {
                pEvent->create<Event::GamePause::Builder>();
            }
        }
    }
}
