#pragma once
#if ABYSS_DEBUG
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IUpdate.hpp>

namespace abyss::Actor::Player
{
    class DebugCtrl :
        public IComponent,
        public IUpdate
    {
    private:
        ActorObj* m_pActor;
    public:
        DebugCtrl(ActorObj* pActor);

        void onUpdate() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::DebugCtrl>
    {
        using Base = Actor::IUpdate;
    };
}

#endif