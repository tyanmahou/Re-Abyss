#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Player::Shot
{
    class PlayerShot;

    /// <summary>
    /// 当たり判定
    /// </summary>
    class Collider :
        public IComponent,
        public ICollider
    {
    private:
        Ref<Body> m_body;
        Ref<PlayerShot> m_shot;
    public:
        using ICollider::ICollider;

        void setup() override;

        s3d::Circle getColliderCircle() const;
        CShape getCollider() const override;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Player::Shot::Collider>
    {
        using Base = Actor::ICollider;
    };
}