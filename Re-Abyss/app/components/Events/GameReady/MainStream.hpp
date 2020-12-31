#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/IStream.hpp>

namespace abyss::Event::GameReady
{
    class MainStream : 
        public IComponent,
        public IStream
    {
    public:
        MainStream(IEvent* pEvent);

        void setup(Executer executer) override;
        void onStart() override;

        Coro::Task<> onExecute() override;
    private:
        IEvent* m_pEvent;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::GameReady::MainStream>
    {
        using Base = MultiComponents<Event::IStream>;
    };
}