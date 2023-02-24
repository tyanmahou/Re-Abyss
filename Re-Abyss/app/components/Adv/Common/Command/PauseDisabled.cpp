#include <abyss/components/Adv/Common/Command/PauseDisabled.hpp>
#include <abyss/modules/Pause/PauseManager.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    PauseDisabled::PauseDisabled(AdvObj* pObj, bool isDisabled):
        m_pObj(pObj),
        m_isDisabled(isDisabled)
    {
    }
    void PauseDisabled::onStart()
    {
        if (auto* pPause = m_pObj->getModule<Pause::PauseManager>()) {
            pPause->setPausable(!m_isDisabled, Pause::PauseManager::DisableKind::Demo);
        }
    }
    Coro::Fiber<> PauseDisabled::onCommand()
    {
        co_return;
    }
}
