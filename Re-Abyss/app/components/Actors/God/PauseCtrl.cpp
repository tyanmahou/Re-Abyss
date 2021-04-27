#include "PauseCtrl.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Events/GamePause/Builder.hpp>


namespace abyss::Actor::God
{
    PauseCtrl::PauseCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void PauseCtrl::onUpdate()
    {
        if (InputManager::Start.down()) {
            m_pActor->getModule<Events>()->create<Event::GamePause::Builder>();
        }
    }
}
