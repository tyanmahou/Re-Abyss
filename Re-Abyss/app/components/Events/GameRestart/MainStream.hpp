#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/IStream.hpp>
#include <abyss/components/Events/base/IGlobalTimeScale.hpp>

namespace abyss::Event::GameRestart
{
    class MainStream : 
        public IComponent,
        public IStream,
        public IGlobalTimeScale
    {
    public:
        MainStream(IEvent* pEvent);

        void setup(Depends depends) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;

        double getGlobalTimeScale() const override;
    private:
        IEvent* m_pEvent;
        double m_globalTimeScale = 1.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::GameRestart::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream,
            Event::IGlobalTimeScale
        >;
    };
}