#pragma once
#if ABYSS_DEBUG
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/IUpdate.hpp>

namespace abyss::Actor::Player
{
    class DebugCtrl :
        public IComponent,
        public IUpdate
    {
    private:
        IActor* m_pActor;
    public:
        DebugCtrl(IActor* pActor);

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