#pragma once
#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::God
{
    class PauseModel:
        public IComponent,
        public IUpdateModel
    {
        IActor* m_pActor = nullptr;
    public:
        PauseModel(IActor* pActor);
        void onUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::God::PauseModel>
    {
        using Base = IUpdateModel;
    };
}
