#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Col
{
    /// <summary>
    /// 体当たり判定
    /// </summary>
    class BodyCollider :
        public ICollider
    {
    public:
        BodyCollider(ActorObj* pActor);

        void onStart() override;

        CShape getCollider() const override;
    private:
        ActorObj* m_pActor;
        Ref<Body> m_body;
    };
}