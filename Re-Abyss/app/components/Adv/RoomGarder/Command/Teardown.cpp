#include <abyss/components/Adv/RoomGarder/Command/Teardown.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

namespace abyss::Adv::RoomGarder
{
    Teardown::Teardown(AdvObj* pObj) :
        m_pObj(pObj)
    {}

    void Teardown::onStart()
    {
        m_pObj->getModule<RoomManager>()->unlockRoomGarder();
    }

    Coro::Fiber<> Teardown::onCommand()
    {
        co_return;
    }
}
