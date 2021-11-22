#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Col
{
    /// <summary>
    /// 矩形当たり判定
    /// </summary>
    class RectCollider :
        public ICollider
    {
    public:
        RectCollider(ActorObj* pActor, Ref<ILocator> locator = nullptr);

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