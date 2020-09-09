#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsVM;

    class Draw :
        public IComponent,
        public IDrawModel
    {
    private:
        IActor* m_pActor;
        Ref<ViewCtrl<OopartsVM>> m_view;
    public:
        Draw(IActor* pActor);
        void setup() override;
        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Ooparts::Draw>
    {
        using Base = IDrawModel;
    };
}