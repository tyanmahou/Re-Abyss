#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class MainCollider final: public Col::ICollider
    {
    private:
        void onStart() override;
        CShape getCollider() const override;
    public:
        MainCollider(ActorObj* pActor);
    private:
        ActorObj* m_pActor = nullptr;
        Ref<Body> m_body;
        Ref<ScaleCtrl> m_scale;
    };
}