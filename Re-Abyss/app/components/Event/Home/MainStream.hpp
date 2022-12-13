#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>

namespace abyss::Event::Home
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

        Coro::Fiber<> onExecute() override;
    private:
        EventObj* m_pEvent;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Home::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}
