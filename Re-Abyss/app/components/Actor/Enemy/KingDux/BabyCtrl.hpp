#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class BabyCtrl final :
        public IComponent,
        public ILastUpdate
    {
    public:
        BabyCtrl(ActorObj* pActor);

        void add(const Ref<ActorObj>& baby);

        void onLastUpdate() override;

        bool isExistBaby() const;
    private:
        ActorObj* m_pActor = nullptr;
        s3d::Array<Ref<ActorObj>> m_babies;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Enemy::KingDux::BabyCtrl>
    {
        using Base = MultiComponents<
            Actor::ILastUpdate
        >;
    };
}