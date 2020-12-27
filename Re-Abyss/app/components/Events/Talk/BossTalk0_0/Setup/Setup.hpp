#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/Talk/base/ITalker.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    class Setup : 
        public IComponent,
        public ITalker
    {
    public:
        Setup(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onTalk() override;

    private:
        TalkObj* m_pTalk;
    };
}