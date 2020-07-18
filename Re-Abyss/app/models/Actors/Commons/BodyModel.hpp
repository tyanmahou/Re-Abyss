#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Optional.hpp>

#include <abyss/types/MapColInfo.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
namespace abyss
{
    class BodyModel : public IComponent
    {
    private:
        s3d::Vec2 m_prevPos{ 0, 0 };
        s3d::Vec2 m_pos{0, 0};
        s3d::Vec2 m_pivot{ 0, 0 };

        s3d::Vec2 m_velocity{0, 0};

        s3d::Vector2D <s3d::Optional<double>> m_minVelocity;
        s3d::Vector2D <s3d::Optional<double>> m_maxVelocity;

        s3d::Vec2 m_accel{0, DefaultGravity};
        double m_decelX = 0.0;

        Forward m_forward{Forward::None};

        s3d::Vec2 m_size{ 0, 0 };

        IActor* m_pActor;
    public:
        BodyModel(IActor* pActor);

        void update(double dt);

        BodyModel& setAccel(const s3d::Vec2& accel);
        BodyModel& setAccelX(double accel);
        BodyModel& setAccelY(double accel);

        BodyModel& setDecelX(double deccel);

        BodyModel& setVelocity(const s3d::Vec2& velocity);
        BodyModel& setVelocityX(double velocity);
        BodyModel& setVelocityY(double velocity);
        const s3d::Vec2& getVelocity() const;

        BodyModel& setMaxSpeedX(double speed);
        BodyModel& setMaxSpeedX(s3d::None_t);

        BodyModel& setMaxSpeedY(double speed);
        BodyModel& setMaxSpeedY(s3d::None_t);

        BodyModel& setMaxSpeed(const s3d::Vec2& speed);
        BodyModel& setMaxSpeed(s3d::None_t);

        BodyModel& setMaxVelocityY(double velocity);
        BodyModel& setMaxVelocityY(s3d::None_t);

        BodyModel& initPos(const s3d::Vec2& pos);
        BodyModel& setPos(const s3d::Vec2& pos);
        BodyModel& setPosX(double x);
        BodyModel& setPosY(double y);
        BodyModel& addPos(const s3d::Vec2& deltaPos);
        BodyModel& addPosX(double deltaX);
        BodyModel& addPosY(double deltaY);

        const s3d::Vec2& getPos() const;
        const s3d::Vec2& getPrevPos() const;

        BodyModel& setForward(Forward forward);

        Forward getForward() const;

        BodyModel& setSize(const s3d::Vec2& size);
        const s3d::Vec2& getSize() const;
        double getWidth() const;
        double getHeight() const;

        BodyModel& setPivot(const s3d::Vec2& pivot);
        const s3d::Vec2& getPivot() const;
        s3d::Vec2 getPivotPos() const;

        s3d::RectF region() const;

        void jump(double speed);
        void jumpToHeight(double height);

        BodyModel& noneResistanced();
        BodyModel& reversed();

        bool isForward(Forward f) const;

        ColDirection fixPos(const MapColInfo& info);
        ColDirection fixPos(const RoomModel& room, bool isStrict = false);

    public:
        inline static constexpr double DefaultGravity = 720.0;
        inline static constexpr double DefaultMaxVelocityY = 78;
    };
}