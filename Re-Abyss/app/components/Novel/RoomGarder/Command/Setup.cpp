#include <abyss/components/Novel/RoomGarder/Command/Setup.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::RoomGarder
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
    }

    Coro::Task<> Setup::onCommand()
    {
        co_return;
    }
}
