#include <abyss/components/Novel/Common/EventCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Stage/Stage.hpp>

namespace abyss::Novel
{
    EventCtrl::EventCtrl(TalkObj* pTalk, s3d::uint32 eventId):
        m_pTalk(pTalk),
        m_eventId(eventId)
    {
    }
    void EventCtrl::requestComplete()
    {
        m_pTalk->getModule<Temporary>()->saveFlagExit(tempKey());
    }
    void EventCtrl::onStart()
    {
        if (m_pTalk->getModule<Temporary>()->onFlag(tempKey())) {
            m_pTalk->destroy();
        }
    }
    TempKey EventCtrl::tempKey() const
    {
        return TempKey::EventComplete(
            m_pTalk->getModule<Stage>()->mapName(),
            m_eventId
        );
    }
}
