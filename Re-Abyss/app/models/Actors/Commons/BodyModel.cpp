#include "BodyModel.hpp"
#include <Siv3D/Math.hpp>
namespace abyss
{

    void BodyModel::update(double dt)
    {
        m_prevPos = m_pos;
        // 速度更新
        m_velocity += m_accel * dt;

        m_maxSpeedX.then([this](double max) {
            if (m_velocity.x > max) {
                m_velocity.x = max;
            } else if (m_velocity.x < -max) {
                m_velocity.x = -max;
            }
        });

        if (m_accel.x == 0.0) {
            if (m_velocity.x > 0) {
                m_velocity.x -= m_deccelX * dt;
            } else if (m_velocity.x < 0) {
                m_velocity.x += m_deccelX * dt;
            }
            if (s3d::Abs(m_velocity.x) < 0.6) {
                m_velocity.x = 0;
            }
        }
        m_maxVelocityY.then([this](double max) {
            if (m_velocity.y > max) {
                m_velocity.y = max;
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
    BodyModel& BodyModel::setDeccelX(double deccel)
    {
        m_deccelX = deccel;
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
        m_maxSpeedX = speed;
        return *this;
    }
    BodyModel& BodyModel::setMaxSpeedX(s3d::None_t)
    {
        m_maxSpeedX = s3d::none;
        return *this;
    }
    BodyModel& BodyModel::setMaxVelocityY(double velocity)
    {
        m_maxVelocityY = velocity;
        return *this;
    }
    BodyModel& BodyModel::setMaxVelocityY(s3d::None_t)
    {
        m_maxVelocityY = s3d::none;
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
            .setDeccelX(0)
            .setMaxVelocityY(s3d::none)
            .setMaxSpeedX(s3d::none);
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
    s3d::RectF BodyModel::region() const
    {
        return { m_pos + m_pivot - m_size / 2, m_size };
    }
}
