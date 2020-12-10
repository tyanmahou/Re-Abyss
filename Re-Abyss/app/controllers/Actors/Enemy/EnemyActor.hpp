#pragma once

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>

namespace abyss::Actor::Enemy
{
    class EnemyActor :
        public IActor,
        public Receiver
    {
        friend class EnemyBuilder;
    protected:
        Ref<Body> m_body;
        Ref<HP> m_hp;
    public:
        EnemyActor() = default;

        const s3d::Vec2& getPos()const;
        const s3d::Vec2& getVelocity()const;

        Forward getForward()const;
        bool accept(const ActVisitor& visitor) override;

        const Body& getBody()const;
        Body& getBody();
        const HP& getHp()const;
        CShape getCollider() const;
        s3d::RectF region()const;
    };

}