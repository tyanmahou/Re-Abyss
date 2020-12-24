#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/IStream.hpp>

namespace abyss::Event::GamePause
{
    class MainStream : 
        public IComponent,
        public IStream
    {
    public:
        MainStream(IEvent* pEvent);

        void setup(Depends depends) override;
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
    struct ComponentTree<Event::GamePause::MainStream>
    {
        using Base = MultiComponents<Event::IStream>;
    };
}