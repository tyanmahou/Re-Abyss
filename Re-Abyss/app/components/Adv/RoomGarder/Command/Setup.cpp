#include <abyss/components/Adv/RoomGarder/Command/Setup.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

namespace abyss::Adv::RoomGarder
{
    Setup::Setup(AdvObj* pObj):
        m_pObj(pObj)
    {}

    void Setup::onStart()
    {
        m_pObj->getModule<RoomManager>()->requestRoomGarder();
    }

    Coro::Fiber<> Setup::onCommand()
    {
        co_return;
    }
}
