#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class ForwardCtrl final :
        public IComponent,
        public ILastUpdate
    {
    public:
        ForwardCtrl(ActorObj* pActor);

        void onStart() override;

        void onLastUpdate() override;
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::KingDux::BabyDux::ForwardCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate
        >;
    };
}
