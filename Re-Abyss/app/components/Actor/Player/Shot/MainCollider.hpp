#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Actor/Common/Col/Collider/ICollider.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Player::Shot
{
    class PlayerShot;

    /// <summary>
    /// 当たり判定
    /// </summary>
    class MainCollider :
        public IComponent,
        public Col::ICollider
    {
    public:
        MainCollider(ActorObj* pActor);

        void onStart() override;

        s3d::Circle getColliderCircle() const;
        CShape getCollider() const override;

    private:
        ActorObj* m_pActor;
        Ref<Body> m_body;
        Ref<PlayerShot> m_shot;
    };
}