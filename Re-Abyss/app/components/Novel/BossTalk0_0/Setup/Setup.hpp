#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Novel/base/ITalker.hpp>

namespace abyss::Novel::BossTalk0_0
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

namespace abyss
{
    template<>
    struct ComponentTree<Novel::BossTalk0_0::Setup>
    {
        using Base = MultiComponents<
            Novel::ITalker
        >;
    };
}