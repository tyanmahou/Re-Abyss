#pragma once
#pragma once
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::God
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
    struct ComponentTree<God::PauseModel>
    {
        using Base = IUpdateModel;
    };
}
