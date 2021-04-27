#pragma once
#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::God
{
    class PauseCtrl:
        public IComponent,
        public IUpdate
    {
        ActorObj* m_pActor = nullptr;
    public:
        PauseCtrl(ActorObj* pActor);
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
