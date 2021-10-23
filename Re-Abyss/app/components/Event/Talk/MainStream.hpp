#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Talk
{
    class MainStream :
        public IComponent,
        public IStream
    {
    public:
        MainStream(EventObj* pEvent, Ref<Novel::TalkObj> talk);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;
    private:
        EventObj* m_pEvent;
        Ref<Novel::TalkObj> m_talk;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Talk::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}