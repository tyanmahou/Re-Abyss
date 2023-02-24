#include <abyss/components/Adv/Common/EventCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Stage/Stage.hpp>

namespace abyss::Adv
{
    EventCtrl::EventCtrl(AdvObj* pObj, s3d::uint32 eventId):
        m_pObj(pObj),
        m_eventId(eventId)
    {
    }
    void EventCtrl::requestComplete()
    {
        m_pObj->getModule<Temporary>()->saveFlagExit(tempKey());
    }
    void EventCtrl::onStart()
    {
        if (m_pObj->getModule<Temporary>()->onFlag(tempKey())) {
            m_pObj->destroy();
        }
    }
    TempKey EventCtrl::tempKey() const
    {
        return TempKey::EventComplete(
            m_pObj->getModule<Stage>()->mapName(),
            m_eventId
        );
    }
}
