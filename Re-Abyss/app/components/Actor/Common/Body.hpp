#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/RectF.hpp>
#include <Siv3D/Optional.hpp>

#include <abyss/values/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/components/Actor/Common/BodyAnchor.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>

namespace abyss::Actor
{
    class Body : 
        public IComponent,
        public ILocator
    {
    public:
        inline static constexpr double DefaultGravity = 720.0;
        inline static constexpr double DefaultMaxVelocityY = 78;

    public:
        Body(ActorObj* pActor);

        void update(double dt);

        Body& setAccel(const s3d::Vec2& accel);
        Body& setAccelX(double accel);
        Body& setAccelY(double accel);

        Body& setDecelX(double deccel);

        Body& setVelocity(const s3d::Vec2& velocity);
        Body& setVelocityX(double velocity);
        Body& setVelocityY(double velocity);
        const s3d::Vec2& getVelocity() const;

        Body& setMaxSpeedX(double speed);
        Body& setMaxSpeedX(s3d::None_t);

        Body& setMaxSpeedY(double speed);
        Body& setMaxSpeedY(s3d::None_t);

        Body& setMaxSpeed(double speed);
        Body& setMaxSpeed(const s3d::Vec2& speed);
        Body& setMaxSpeed(s3d::None_t);

        Body& setMaxVelocityY(double velocity);
        Body& setMaxVelocityY(s3d::None_t);

        Body& initPos(const s3d::Vec2& pos);
        Body& setPos(const s3d::Vec2& pos);
        Body& setPosX(double x);
        Body& setPosY(double y);
        Body& addPos(const s3d::Vec2& deltaPos);
        Body& addPosX(double deltaX);
        Body& addPosY(double deltaY);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getPrevPos() const;

        Body& setForward(Forward forward);

        Forward getForward() const;

        Body& initSize(const s3d::Vec2& size);
        Body& setSize(const s3d::Vec2& size);
        const s3d::Vec2& getSize() const;
        double getWidth() const;
        double getHeight() const;

        Body& initOffset(const s3d::Vec2& offset);
        Body& setOffset(const s3d::Vec2& offset);
        const s3d::Vec2& getOffset() const;
        s3d::Vec2 getOffsetedPos() const;
        s3d::Vec2 getOffsetedPosPrev() const;

        Body& setAnchor(BodyAnchor anchor);

        s3d::RectF region() const;
        s3d::RectF prevRegion() const;

        void jump(double speed);
        void jumpToHeight(double height);

        void moveToPos(const s3d::Vec2& pos, double dt);

        Body& noneResistanced();
        Body& reversed();

        Body& addForce(const s3d::Vec2& force);
        Body& addImpulse(const s3d::Vec2& impulse);

        bool isForward(Forward f) const;

        ColDirection fixPos(const Physics::TerrainData& terrain);
        ColDirection fixPos(const Room::RoomData& room, const s3d::Optional<ColDirection>& strict = s3d::none);

        s3d::Vec2 getCenterPos()const override;
        Body& setCenterPos(const s3d::Vec2& pos);

        s3d::Vec2 moveDiff() const;
    private:
        s3d::Vec2 m_prevPos{ 0, 0 };
        s3d::Vec2 m_pos{ 0, 0 };

        s3d::Vec2 m_offset{ 0, 0 };
        s3d::Vec2 m_offsetPrev{ 0, 0 };
        s3d::Vec2 m_offsetNext{ 0, 0 };

        s3d::Vec2 m_velocity{ 0, 0 };

        s3d::Vector2D <s3d::Optional<double>> m_minVelocity;
        s3d::Optional<double> m_minSpeed;
        s3d::Vector2D <s3d::Optional<double>> m_maxVelocity;
        s3d::Optional<double> m_maxSpeed;

        s3d::Vec2 m_accel{ 0, DefaultGravity };
        double m_decelX = 0.0;

        Forward m_forward{ Forward::None() };

        s3d::Vec2 m_size{ 0, 0 };
        s3d::Vec2 m_sizePrev{ 0, 0 };
        s3d::Vec2 m_sizeNext{ 0, 0 };

        BodyAnchor m_anchor{BodyAnchor::Center};

        ActorObj* m_pActor;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::Body>
    {
        using Base = Actor::ILocator;
    };
}
