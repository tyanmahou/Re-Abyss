#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Event/base/IStream.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Event::Splash
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
        Ref<UI::UIObj> m_pLogo;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::Splash::MainStream>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}