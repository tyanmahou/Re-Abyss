#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Novel/base/ICommand.hpp>

namespace abyss::Novel::RoomGarder
{
    class Setup : 
        public ICommand
    {
    public:
        Setup(TalkObj* pTalk);

        void onStart() override;

        Coro::Fiber<> onCommand() override;

    private:
        TalkObj* m_pTalk;
    };
}
