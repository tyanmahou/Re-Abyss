#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>

namespace abyss::Event::SaveSelect
{
    class MainStream :
        public IComponent,
        public IStream
    {
    public:
        MainStream(IEvent* pEvent);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;
    private:
        IEvent* m_pEvent;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::SaveSelect::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}