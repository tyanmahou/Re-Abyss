#include "PauseModel.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Event/GamePause/GamePause.hpp>


namespace abyss::God
{
    PauseModel::PauseModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void PauseModel::onUpdate([[maybe_unused]]double dt)
    {
        if (InputManager::Start.down()) {
            m_pActor->getModule<Events>()->create<Event::GamePause>();
        }
    }
}
