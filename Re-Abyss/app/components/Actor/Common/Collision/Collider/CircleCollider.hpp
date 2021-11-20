#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Collision/Collider/ICollider.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Collision
{
    /// <summary>
    /// 円当たり判定
    /// </summary>
    class CircleCollider :
        public ICollider
    {
    private:
        ActorObj* m_pActor;
        Ref<ILocator> m_locator;
        double m_radius = 0.0;
    public:
        CircleCollider(ActorObj* pActor, Ref<ILocator> locator = nullptr);

        void onStart() override;

        CShape getCollider() const override;

        CircleCollider& setRadius(double radius)
        {
            m_radius = radius;
            return *this;
        }
    };
}