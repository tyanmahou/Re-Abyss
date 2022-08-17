#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/TargetCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class MainCollider final : public Col::ICollider
    {
    private:
        void onStart() override;
        CShape getCollider() const override;
    public:
        MainCollider(ActorObj* pActor);
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<TargetCtrl> m_target;
    };
}
