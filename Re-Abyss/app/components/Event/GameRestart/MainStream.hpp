#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Event/base/IStream.hpp>
#include <abyss/components/Event/Common/IGlobalTimeScale.hpp>

namespace abyss::Event::GameRestart
{
    class MainStream : 
        public IComponent,
        public IStream,
        public IGlobalTimeScale
    {
    public:
        MainStream(EventObj* pEvent);

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;

        double getGlobalTimeScale() const override;
    private:
        EventObj* m_pEvent;
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