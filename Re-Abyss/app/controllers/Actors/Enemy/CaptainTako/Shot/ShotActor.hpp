#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::Actor::CaptainTako::Shot
{
    class ShotVM;

    class ShotActor:
        public IActor,
        public Attacker
    {
    private:
        Ref<BodyModel> m_body;
    public:
        ShotActor(const s3d::Vec2& pos, Forward forward);

        CShape getCollider() const;

        s3d::Circle getColliderCircle() const;

        bool accept(const ActVisitor& visitor) override;
    };
}