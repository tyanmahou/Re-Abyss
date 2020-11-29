#pragma once
#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IUpdate.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::God
{
    class PauseCtrl:
        public IComponent,
        public IUpdate
    {
        IActor* m_pActor = nullptr;
    public:
        PauseCtrl(IActor* pActor);
        void onUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::God::PauseCtrl>
    {
        using Base = Actor::IUpdate;
    };
}
