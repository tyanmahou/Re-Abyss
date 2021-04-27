#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>
#include <abyss/components/Actor/Commons/ViewCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsView;

    class Draw :
        public IComponent,
        public IDraw
    {
    private:
        ActorObj* m_pActor;
        Ref<ViewCtrl<OopartsView>> m_view;
    public:
        Draw(ActorObj* pActor);
        void onStart() override;
        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Ooparts::Draw>
    {
        using Base = Actor::IDraw;
    };
}