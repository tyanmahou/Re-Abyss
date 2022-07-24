#include <abyss/components/Novel/Common/Command/PauseDisabled.hpp>
#include <abyss/modules/Pause/PauseManager.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    PauseDisabled::PauseDisabled(TalkObj* pTalk, bool isDisabled):
        m_pTalk(pTalk),
        m_isDisabled(isDisabled)
    {
    }
    void PauseDisabled::onStart()
    {
        if (auto* pPause = m_pTalk->getModule<Pause::PauseManager>()) {
            pPause->setPausable(!m_isDisabled, Pause::PauseManager::DisableKind::Demo);
        }
    }
    Coro::Task<> PauseDisabled::onCommand()
    {
        co_return;
    }
}
