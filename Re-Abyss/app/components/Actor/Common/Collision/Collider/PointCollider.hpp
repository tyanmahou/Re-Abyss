#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Collision/Collider/ICollider.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Collision
{
    /// <summary>
    /// 点当たり判定
    /// </summary>
    class PointCollider :
        public ICollider
    {
    private:
        ActorObj* m_pActor;
        Ref<ILocator> m_locator;
    public:
        PointCollider(ActorObj* pActor, Ref<ILocator> locator = nullptr);

        void onStart() override;

        CShape getCollider() const override
        {
            return m_locator->getCenterPos();
        }
    };
}