#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Event/base/IStream.hpp>

namespace abyss::Event::GameReady
{
    class MainStream : 
        public IComponent,
        public IStream
    {
    public:
        MainStream(EventObj* pEvent);

        void setup(Executer executer) override;
        void onStart() override;

        Coro::Fiber<> onExecute() override;
    private:
        EventObj* m_pEvent;
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