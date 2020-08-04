#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Ooparts
{
    class OopartsVM;

    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    private:
        IActor* m_pActor;
        Ref<ViewModel<OopartsVM>> m_view;
    public:
        DrawModel(IActor* pActor);
        void setup() override;
        void onDraw() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Ooparts::DrawModel>
    {
        using Base = IDrawModel;
    };
}