#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor::Enemy::Schield::Shot
{
    class ShotVM;

    class ShotActor :
        public IActor,
        public Attacker
    {
    private:
        Ref<Body> m_body;
    public:
        ShotActor(const s3d::Vec2& pos, const s3d::Vec2& dir);

        CShape getCollider() const;
        s3d::Circle getColliderCircle() const;

        bool accept(const ActVisitor& visitor) override;
    };
}