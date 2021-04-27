#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/Talk/base/ITalker.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    class Teardown :
        public IComponent,
        public ITalker
    {
    public:
        Teardown(TalkObj* pTalk);

        void onStart() override;

        Coro::Task<> onTalk() override;

    private:
        TalkObj* m_pTalk;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Talk::BossTalk0_0::Teardown>
    {
        using Base = MultiComponents<
            Event::Talk::ITalker
        >;
    };
}