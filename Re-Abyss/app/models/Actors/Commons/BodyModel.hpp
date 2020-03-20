#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Optional.hpp>

#include <abyss/types/Forward.hpp>

namespace abyss
{
    class BodyModel
    {
    private:
        s3d::Vec2 m_pos{0, 0};
        s3d::Vec2 m_pivot{ 0, 0 };

        s3d::Vec2 m_velocity{0, 0};
        s3d::Optional<double> m_maxSpeedX;
        s3d::Optional<double> m_maxVelocityY = DefaultMaxVelocityY;

        s3d::Vec2 m_accel{0, DefaultGravity};
        double m_deccelX = 0.0;

        Forward m_forward{Forward::None};

        s3d::Vec2 m_size{ 0, 0 };
    public:
        BodyModel() = default;
       
        void update(double dt);

        BodyModel& setAccel(const s3d::Vec2& accel);
        BodyModel& setAccelX(double accel);
        BodyModel& setAccelY(double accel);

        BodyModel& setDeccelX(double deccel);

        BodyModel& setVelocity(const s3d::Vec2& velocity);
        BodyModel& setVelocityX(double velocity);
        BodyModel& setVelocityY(double velocity);
        const s3d::Vec2& getVelocity() const;

        BodyModel& setMaxSpeedX(double speed);
        BodyModel& setMaxSpeedX(s3d::None_t);

        BodyModel& setMaxVelocityY(double velocity);
        BodyModel& setMaxVelocityY(s3d::None_t);

        BodyModel& setPos(const s3d::Vec2& pos);
        BodyModel& setPosX(double x);
        BodyModel& setPosY(double y);
        BodyModel& addPos(const s3d::Vec2& deltaPos);
        BodyModel& addPosX(double deltaX);
        BodyModel& addPosY(double deltaY);

        const s3d::Vec2& getPos() const;

        BodyModel& setForward(Forward forward);

        Forward getForward() const;

        BodyModel& setSize(const s3d::Vec2& size);
        const s3d::Vec2& getSize() const;

        BodyModel& setPivot(const s3d::Vec2& pivot);

        s3d::RectF region() const;

        void jump(double speed);
        void jumpToHeight(double height);

        BodyModel& noneResistanced();
        BodyModel& reversed();

        bool isForward(Forward f) const;
    public:
        inline static constexpr double DefaultGravity = 720.0;
        inline static constexpr double DefaultMaxVelocityY = 78;
    };
}