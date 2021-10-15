#pragma once
#include <memory>
#include <queue>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Novel/base/ITalker.hpp>
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
        std::queue<std::shared_ptr<ITalker>> m_talks;
        bool m_doneCurrentInit = false;
    };
}