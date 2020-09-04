#pragma once
#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::God
{
    class PauseCtrl:
        public IComponent,
        public IUpdateModel
    {
        IActor* m_pActor = nullptr;
    public:
        PauseCtrl(IActor* pActor);
        void onUpdate(double dt) override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::God::PauseCtrl>
    {
        using Base = IUpdateModel;
    };
}
