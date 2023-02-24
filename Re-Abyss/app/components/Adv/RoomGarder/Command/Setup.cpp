#include <abyss/components/Adv/RoomGarder/Command/Setup.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

namespace abyss::Adv::RoomGarder
{
    Setup::Setup(AdvObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        m_pTalk->getModule<RoomManager>()->requestRoomGarder();
    }

    Coro::Fiber<> Setup::onCommand()
    {
        co_return;
    }
}
