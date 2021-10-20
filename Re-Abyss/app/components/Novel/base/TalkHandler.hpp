#pragma once
#include <memory>
#include <queue>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Novel/base/ICommand.hpp>
#include <abyss/utils/Coro/TaskHolder/TaskHolder.hpp>

namespace abyss::Novel
{
    class TalkHandler : public IComponent
    {
    public:
        TalkHandler(TalkObj* pTalk);

        void setup(Executer executer) override;

        void onStart() override;
        void onEnd() override;

        bool update();
    private:
        TalkObj* m_pTalk;
        Coro::TaskHolder<> m_stream;
        std::queue<std::shared_ptr<ICommand>> m_commands;
        bool m_doneCurrentInit = false;
    };
}