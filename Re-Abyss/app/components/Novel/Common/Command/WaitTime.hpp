#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Novel
{
    class WaitTime :
        public ICommand
    {
    public:
        WaitTime(TalkObj* pTalk, const s3d::Duration& waitTime);

        Coro::Fiber<> onCommand() override;

    private:
        Coro::Fiber<> wait();
        Coro::Fiber<> skip();
    private:
        TalkObj* m_pTalk = nullptr;
        s3d::Duration m_waitTime;
    };
}