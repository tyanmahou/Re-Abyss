#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Ooparts
{
    class KiraKiraCtrl :
        public IComponent,
        public IPreDraw
    {
    public:
        KiraKiraCtrl(ActorObj* pActor);

        void setup(Executer executer) override;
        void onStart() override;
        void onPreDraw() override;
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;

        TimeLite::IntervalTimer m_intervalTimer;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Ooparts::KiraKiraCtrl>
    {
        using Base = Actor::IPreDraw;
    };
}