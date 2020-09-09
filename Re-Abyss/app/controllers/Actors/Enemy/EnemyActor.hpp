#pragma once

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy
{
    class EnemyActor :
        public IActor,
        public Attacker,
        public Receiver
    {
        friend class EnemyBuilder;
    protected:
        Ref<BodyModel> m_body;
        Ref<HP> m_hp;
    public:
        EnemyActor() = default;

        EnemyActor(const s3d::Vec2& pos, Forward forward = Forward::Left);

        const s3d::Vec2& getPos()const;
        const s3d::Vec2& getVelocity()const;

        Forward getForward()const;
        bool accept(const ActVisitor& visitor) override;

        const BodyModel& getBody()const;
        BodyModel& getBody();
        const HP& getHp()const;
        CShape getCollider() const;
        s3d::RectF region()const;
    };

}