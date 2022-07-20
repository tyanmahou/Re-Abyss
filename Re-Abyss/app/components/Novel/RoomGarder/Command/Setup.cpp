#include <abyss/components/Novel/RoomGarder/Command/Setup.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

namespace abyss::Novel::RoomGarder
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        m_pTalk->getModule<RoomManager>()->requestRoomGarder();
    }

    Coro::Task<> Setup::onCommand()
    {
        co_return;
    }
}
