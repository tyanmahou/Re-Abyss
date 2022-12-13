#include <abyss/components/Novel/RoomGarder/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
namespace abyss::Novel::RoomGarder
{
    Teardown::Teardown(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void Teardown::onStart()
    {
        m_pTalk->getModule<RoomManager>()->unlockRoomGarder();
    }

    Coro::Fiber<> Teardown::onCommand()
    {
        co_return;
    }
}
