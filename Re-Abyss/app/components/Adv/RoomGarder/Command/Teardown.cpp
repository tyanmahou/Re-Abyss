#include <abyss/components/Adv/RoomGarder/Command/Teardown.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

namespace abyss::Adv::RoomGarder
{
    Teardown::Teardown(AdvObj* pTalk) :
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
