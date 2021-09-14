#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>

namespace abyss::Event::Title
{
    class MainStream :
        public IComponent,
        public IStream
    {
    public:
        MainStream(EventObj* pEvent);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;
    private:
        EventObj* m_pEvent;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Title::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}