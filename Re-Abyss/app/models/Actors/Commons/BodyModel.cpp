#include "BodyModel.hpp"
#include <Siv3D/Math.hpp>
#include <abyss/models/Collision/FixPos.hpp>
#include <abyss/models/Room/RoomModel.hpp>

namespace abyss
{
    BodyModel::BodyModel()
    {
        m_maxVelocity.y = DefaultMaxVelocityY;
    }

    void BodyModel::update(double dt)
    {
        m_prevPos = m_pos;
        // 速度更新
        m_velocity += m_accel * dt;

        m_maxVelocity.x.then([this](double max) {
            if (m_velocity.x > max) {
                m_velocity.x = max;
            }
        });
        m_minVelocity.x.then([this](double min) {
            if (m_velocity.x < min) {
                m_velocity.x = min;
            }
        });

        if (m_accel.x == 0.0) {
            if (m_velocity.x > 0) {
                m_velocity.x -= m_decelX * dt;
            } else if (m_velocity.x < 0) {
                m_velocity.x += m_decelX * dt;
            }
            if (s3d::Abs(m_velocity.x) < 0.6) {
                m_velocity.x = 0;
            }
        }
        m_maxVelocity.y.then([this](double max) {
            if (m_velocity.y > max) {
                m_velocity.y = max;
            }
        });
        m_minVelocity.y.then([this](double min) {
            if (m_velocity.y < min) {
                m_velocity.y = min;
            }
        });

        // 座標更新
        m_pos += m_velocity * dt;
    }
    BodyModel& BodyModel::setAccel(const s3d::Vec2& accel)
    {
        m_accel = accel;
        return *this;
    }
    BodyModel& BodyModel::setAccelX(double accel)
    {
        m_accel.x = accel;
        return *this;
    }
    BodyModel& BodyModel::setAccelY(double accel)
    {
        m_accel.y = accel;
        return *this;
    }
    BodyModel& BodyModel::setDecelX(double decel)
    {
        m_decelX = decel;
        return *this;
    }
    BodyModel& BodyModel::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        return *this;
    }
    BodyModel& BodyModel::setVelocityX(double velocity)
    {
        m_velocity.x = velocity;
        return *this;
    }
    BodyModel& BodyModel::setVelocityY(double velocity)
    {
        m_velocity.y = velocity;
        return *this;
    }
    const s3d::Vec2& BodyModel::getVelocity() const
    {
        return m_velocity;
    }
    BodyModel& BodyModel::setMaxSpeedX(double speed)
    {
        double absSpeed = s3d::Math::Abs(speed);
        m_maxVelocity.x = absSpeed;
        m_minVelocity.x = -absSpeed;
        return *this;
    }
    BodyModel& BodyModel::setMaxSpeedX(s3d::None_t)
    {
        m_maxVelocity.x = s3d::none;
        m_minVelocity.x = s3d::none;
        return *this;
    }
    BodyModel& BodyModel::setMaxSpeedY(double speed)
    {
        double absSpeed = s3d::Math::Abs(speed);
        m_maxVelocity.y = absSpeed;
        m_minVelocity.y = -absSpeed;
        return *this;
    }
    BodyModel& BodyModel::setMaxSpeedY(s3d::None_t)
    {
        m_maxVelocity.y = s3d::none;
        m_minVelocity.y = s3d::none;
        return *this;
    }
    BodyModel& BodyModel::setMaxSpeed(const s3d::Vec2& speed)
    {
        return this->
            setMaxSpeedX(speed.x)
            .setMaxSpeedY(speed.y);
    }
    BodyModel& BodyModel::setMaxSpeed(s3d::None_t)
    {
        return this->
            setMaxSpeedX(s3d::none)
            .setMaxSpeedY(s3d::none);
    }
    BodyModel& BodyModel::setMaxVelocityY(double velocity)
    {
        m_maxVelocity.y = velocity;
        return *this;
    }
    BodyModel& BodyModel::setMaxVelocityY(s3d::None_t)
    {
        m_maxVelocity.y = s3d::none;
        return *this;
    }
    BodyModel& BodyModel::initPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        m_prevPos = pos;
        return *this;
    }
    BodyModel& BodyModel::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    BodyModel& BodyModel::setPosX(double x)
    {
        m_pos.x = x;
        return *this;
    }
    BodyModel& BodyModel::setPosY(double y)
    {
        m_pos.y = y;
        return *this;
    }
    BodyModel& BodyModel::addPos(const s3d::Vec2& deltaPos)
    {
        m_pos += deltaPos;
        return *this;
    }
    BodyModel& BodyModel::addPosX(double deltaX)
    {
        m_pos.x += deltaX;
        return *this;
    }
    BodyModel& BodyModel::addPosY(double deltaY)
    {
        m_pos.y += deltaY;
        return *this;
    }
    BodyModel& BodyModel::setSize(const s3d::Vec2& size)
    {
        m_size = size;
        return *this;
    }
    const s3d::Vec2& BodyModel::getSize() const
    {
        return m_size;
    }
    BodyModel& BodyModel::setPivot(const s3d::Vec2& pivot)
    {
        m_pivot = pivot;
        return *this;
    }
    const s3d::Vec2& BodyModel::getPivot() const
    {
        return m_pivot;
    }
    s3d::Vec2 BodyModel::getPivotPos() const
    {
        return m_pos + m_pivot;
    }
    const s3d::Vec2& BodyModel::getPos() const
    {
        return m_pos;
    }
    const s3d::Vec2& BodyModel::getPrevPos() const
    {
        return m_prevPos;
    }
    BodyModel& BodyModel::setForward(Forward forward)
    {
        m_forward = forward;
        return *this;
    }
    Forward BodyModel::getForward() const
    {
        return m_forward;
    }
    void BodyModel::jump(double speed)
    {
        m_velocity.y = -speed;
    }
    void BodyModel::jumpToHeight(double height)
    {
        double v = s3d::Sqrt(2 * m_accel.y * height);
        this->jump(v);
    }
    BodyModel& BodyModel::noneResistanced()
    {
        return this->setAccel({ 0, 0 })
            .setDecelX(0)
            .setMaxSpeed(s3d::none);
    }
    BodyModel& BodyModel::reversed()
    {
        if (m_forward == Forward::Left) {
            m_forward = Forward::Right;
        } else if (m_forward == Forward::Right) {
            m_forward = Forward::Left;
        }
        return *this;
    }
    bool BodyModel::isForward(Forward f) const
    {
        return m_forward == f;
    }
    ColDirection BodyModel::fixPos(const MapColInfo& info)
    {
        auto c = info.col;
        c.ignoredForVelocity(m_velocity);

        auto selfRegion = this->region();
        s3d::Vec2 before = selfRegion.center();
        
        auto [after, colDir] = FixPos::ByPrevPos(info.region, selfRegion, m_prevPos, c);

        this->addPos(after - before);

        return colDir;
    }
    ColDirection BodyModel::fixPos(const RoomModel& room, bool isStrict)
    {
        auto c = isStrict ? ColDirection(ColDirection::All) : room.getCol();
        c.ignoredForVelocity(m_velocity);

        s3d::Vec2 before = this->region().center();

        auto [after, colDir] = FixPos::InnerByLatestPos(room.getRegion(), before, c);

        this->addPos(after - before);

        return colDir;
    }
    s3d::RectF BodyModel::region() const
    {
        return { m_pos + m_pivot - m_size / 2, m_size };
    }
}
