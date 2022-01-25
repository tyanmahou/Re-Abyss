#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class CrownCollider final : public Col::ICollider
    {
    private:
        void onStart() override;
        CShape getCollider() const override;
    public:
        CrownCollider(ActorObj* pActor);
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
    };
}