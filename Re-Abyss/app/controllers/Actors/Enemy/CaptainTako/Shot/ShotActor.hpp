#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor::Enemy::CaptainTako::Shot
{
    class ShotVM;

    class ShotActor:
        public IActor
    {
    private:
        Ref<Body> m_body;
    public:
        ShotActor(const s3d::Vec2& pos, Forward forward);

        CShape getCollider() const;

        s3d::Circle getColliderCircle() const;

        bool accept(const ActVisitor& visitor) override;
    };
}