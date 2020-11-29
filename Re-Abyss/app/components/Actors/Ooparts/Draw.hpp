#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IDraw.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsVM;

    class Draw :
        public IComponent,
        public IDraw
    {
    private:
        IActor* m_pActor;
        Ref<ViewCtrl<OopartsVM>> m_view;
    public:
        Draw(IActor* pActor);
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