#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/IDeadCallback.hpp>

namespace abyss::Actor::Player
{
    class RestartCtrl :
        public IComponent,
        public IDeadCallback
    {
    private:
        ActorObj* m_pActor = nullptr;
    public:
        RestartCtrl(ActorObj* pActor);

        void onDead() override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::RestartCtrl>
    {
        using Base = Actor::IDeadCallback;
    };
}