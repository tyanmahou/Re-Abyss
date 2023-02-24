#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Adv/base/ICommand.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Adv
{
    class WaitTime :
        public ICommand
    {
    public:
        WaitTime(AdvObj* pTalk, const s3d::Duration& waitTime);

        Coro::Fiber<> onCommand() override;

    private:
        Coro::Fiber<> wait();
        Coro::Fiber<> skip();
    private:
        AdvObj* m_pTalk = nullptr;
        s3d::Duration m_waitTime;
    };
}
