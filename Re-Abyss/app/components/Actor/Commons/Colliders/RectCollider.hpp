#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/base/ICollider.hpp>
#include <abyss/components/Actor/base/ILocator.hpp>

namespace abyss::Actor
{
    /// <summary>
    /// 矩形当たり判定
    /// </summary>
    class RectCollider :
        public IComponent,
        public ICollider
    {
    public:
        RectCollider(ActorObj* pActor);

        void onStart() override;

        CShape getCollider() const override;

        RectCollider& setOffset(const s3d::Vec2& offset)
        {
            m_offset = offset;
            return *this;
        }

        RectCollider& setSize(const s3d::Vec2& size)
        {
            m_size = size;
            return *this;
        }
    private:
        ActorObj* m_pActor;
        Ref<ILocator> m_locator;
        s3d::Vec2 m_offset{0, 0};
        s3d::Vec2 m_size{ 0, 0 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::RectCollider>
    {
        using Base = Actor::ICollider;
    };
}