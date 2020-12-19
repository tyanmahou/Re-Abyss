#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/components/Actors/base/ILocator.hpp>
namespace abyss::Actor
{
    /// <summary>
    /// 点当たり判定
    /// </summary>
    class PointCollider :
        public IComponent,
        public ICollider
    {
    private:
        IActor* m_pActor;
        Ref<ILocator> m_locator;
    public:
        PointCollider(IActor* pActor);

        void onStart() override;

        CShape getCollider() const override
        {
            return m_locator->getPos();
        }
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::PointCollider>
    {
        using Base = Actor::ICollider;
    };
}