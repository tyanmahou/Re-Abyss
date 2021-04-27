#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/ICollider.hpp>
#include <abyss/components/Actor/base/ILocator.hpp>
namespace abyss::Actor
{
    /// <summary>
    /// 円当たり判定
    /// </summary>
    class CircleCollider :
        public IComponent,
        public ICollider
    {
    private:
        ActorObj* m_pActor;
        Ref<ILocator> m_locator;
        double m_radius;
    public:
        CircleCollider(ActorObj* pActor);

        void onStart() override;

        CShape getCollider() const override;

        CircleCollider& setRadius(double radius)
        {
            m_radius = radius;
            return *this;
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::CircleCollider>
    {
        using Base = Actor::ICollider;
    };
}