#include <abyss/components/Novel/RoomGarder/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel::RoomGarder
{
    Teardown::Teardown(TalkObj* pTalk) :
        m_pTalk(pTalk)
    {}

    void Teardown::onStart()
    {
    }

    Coro::Task<> Teardown::onCommand()
    {
        co_return;
    }
}
