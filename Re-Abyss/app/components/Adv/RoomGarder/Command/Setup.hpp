#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>

namespace abyss::Adv::RoomGarder
{
    class Setup : 
        public ICommand
    {
    public:
        Setup(AdvObj* pTalk);

        void onStart() override;

        Coro::Fiber<> onCommand() override;

    private:
        AdvObj* m_pTalk;
    };
}
