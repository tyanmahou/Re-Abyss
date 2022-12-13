#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Novel
{
    class MessageStream :
        public ICommand
    {
    public:
        MessageStream(TalkObj* pTalk, const s3d::String& message);

        void onStart() override;
        void onEnd() override;

        Coro::Fiber<> onCommand() override;
    private:
        Coro::Fiber<> stream();
        Coro::Fiber<> skip();
    private:
        TalkObj* m_pTalk = nullptr;
        s3d::String m_message;
        size_t m_done = s3d::String::npos;
    };
}