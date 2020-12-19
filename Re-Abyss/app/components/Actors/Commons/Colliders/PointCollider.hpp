#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <Siv3D/Vector2D.hpp>

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
        s3d::Vec2 m_pos;
    public:
        PointCollider() = default;
        PointCollider(const s3d::Vec2& pos):
            m_pos(pos)
        {}

        PointCollider& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }

        const s3d::Vec2& getPos() const
        {
            return m_pos;
        }

        CShape getCollider() const override
        {
            return m_pos;
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