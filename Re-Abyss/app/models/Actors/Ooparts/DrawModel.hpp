#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>

namespace abyss::Ooparts
{
    class DrawModel :
        public IComponent,
        public IDrawModel
    {
    private:
        OopartsActor* m_pActor;
    public:
        DrawModel(OopartsActor* pActor);
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