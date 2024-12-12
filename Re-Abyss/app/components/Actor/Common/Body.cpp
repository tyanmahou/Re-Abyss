#include <abyss/components/Actor/Common/Body.hpp>
#include <Siv3D/Math.hpp>
#include <abyss/modules/Room/RoomData.hpp>
#include <abyss/utils/Math/Math.hpp>
#include <abyss/utils/Collision/FixPos.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
    Body::Body(ActorObj* pActor):
        m_pActor(pActor)
    {
        m_maxVelocity.y = DefaultMaxVelocityY;
    }

    void Body::update(double dt)
    {
        m_sizePrev = m_size;
        m_size = m_sizeNext;

        m_offsetPrev = m_offset;
        m_offset = m_offsetNext;

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
        m_minSpeed.then([this](double min) {
            if (m_velocity.lengthSq() < min * min) {
                m_velocity.setLength(min);
            }
        });
        m_maxSpeed.then([this](double max) {
            if (m_velocity.lengthSq() > max * max) {
                m_velocity.setLength(max);
            }
        });

        // 減速
        if (m_accel.x == 0.0) {
            auto deltaDecel = m_decelX * dt;
            if (m_velocity.x - deltaDecel > 0) {
                m_velocity.x -= deltaDecel;
            } else if (m_velocity.x + deltaDecel < 0) {
                m_velocity.x += deltaDecel;
            } else {
                m_velocity.x = 0;
            }
        }

        // 座標更新
        m_pos += m_velocity * dt;
    }
    Body& Body::setAccel(const s3d::Vec2& accel)
    {
        m_accel = accel;
        return *this;
    }
    Body& Body::setAccelX(double accel)
    {
        m_accel.x = accel;
        return *this;
    }
    Body& Body::setAccelY(double accel)
    {
        m_accel.y = accel;
        return *this;
    }
    Body& Body::setDecelX(double decel)
    {
        m_decelX = decel;
        return *this;
    }
    Body& Body::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        return *this;
    }
    Body& Body::setVelocityX(double velocity)
    {
        m_velocity.x = velocity;
        return *this;
    }
    Body& Body::setVelocityY(double velocity)
    {
        m_velocity.y = velocity;
        return *this;
    }
    const s3d::Vec2& Body::getVelocity() const
    {
        return m_velocity;
    }
    Body& Body::setMaxSpeedX(double speed)
    {
        double absSpeed = s3d::Math::Abs(speed);
        m_maxVelocity.x = absSpeed;
        m_minVelocity.x = -absSpeed;
        return *this;
    }
    Body& Body::setMaxSpeedX(s3d::None_t)
    {
        m_maxVelocity.x = s3d::none;
        m_minVelocity.x = s3d::none;
        return *this;
    }
    Body& Body::setMaxSpeedY(double speed)
    {
        double absSpeed = s3d::Math::Abs(speed);
        m_maxVelocity.y = absSpeed;
        m_minVelocity.y = -absSpeed;
        return *this;
    }
    Body& Body::setMaxSpeedY(s3d::None_t)
    {
        m_maxVelocity.y = s3d::none;
        m_minVelocity.y = s3d::none;
        return *this;
    }
    Body& Body::setMaxSpeed(double speed)
    {
        m_maxSpeed = s3d::Math::Abs(speed);
        return *this;
    }
    Body& Body::setMaxSpeed(const s3d::Vec2& speed)
    {
        return this->
            setMaxSpeedX(speed.x)
            .setMaxSpeedY(speed.y);
    }
    Body& Body::setMaxSpeed(s3d::None_t)
    {
        m_maxSpeed = s3d::none;
        return this->
            setMaxSpeedX(s3d::none)
            .setMaxSpeedY(s3d::none);
    }
    Body& Body::setMaxVelocityY(double velocity)
    {
        m_maxVelocity.y = velocity;
        return *this;
    }
    Body& Body::setMaxVelocityY(s3d::None_t)
    {
        m_maxVelocity.y = s3d::none;
        return *this;
    }
    Body& Body::initPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        m_prevPos = pos;
        return *this;
    }
    Body& Body::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    Body& Body::setPosX(double x)
    {
        m_pos.x = x;
        return *this;
    }
    Body& Body::setPosY(double y)
    {
        m_pos.y = y;
        return *this;
    }
    Body& Body::addPos(const s3d::Vec2& deltaPos)
    {
        m_pos += deltaPos;
        return *this;
    }
    Body& Body::addPosX(double deltaX)
    {
        m_pos.x += deltaX;
        return *this;
    }
    Body& Body::addPosY(double deltaY)
    {
        m_pos.y += deltaY;
        return *this;
    }
    Body& Body::initSize(const s3d::Vec2& size)
    {
        m_sizePrev = size;
        m_size = size;
        m_sizeNext = size;
        return *this;
    }
    Body& Body::setSize(const s3d::Vec2& size)
    {
        m_sizeNext = size;
        return *this;
    }
    const s3d::Vec2& Body::getSize() const
    {
        return m_size;
    }
    double Body::getWidth() const
    {
        return m_size.x;
    }
    double Body::getHeight() const
    {
        return m_size.y;
    }
    Body& Body::initOffset(const s3d::Vec2& offset)
    {
        m_offsetPrev = offset;
        m_offset = offset;
        m_offsetNext = offset;
        return *this;
    }
    Body& Body::setOffset(const s3d::Vec2& offset)
    {
        m_offsetNext = offset;
        return *this;
    }
    const s3d::Vec2& Body::getOffset() const
    {
        return m_offset;
    }
    s3d::Vec2 Body::getOffsetedPos() const
    {
        return m_pos + m_offset;
    }
    const s3d::Vec2& Body::getPos() const
    {
        return m_pos;
    }
    const s3d::Vec2& Body::getPrevPos() const
    {
        return m_prevPos;
    }
    Body& Body::setForward(Forward forward)
    {
        m_forward = forward;
        return *this;
    }
    Forward Body::getForward() const
    {
        return m_forward;
    }
    void Body::jump(double speed)
    {
        m_velocity.y = -speed;
    }
    void Body::jumpToHeight(double height)
    {
        double v = s3d::Sqrt(2 * m_accel.y * height);
        this->jump(v);
    }
    void Body::moveToPos(const s3d::Vec2& pos, double dt)
    {
        if (abyss::Math::IsZeroLoose(dt)) {
            this->setVelocity(s3d::Vec2::Zero())
                .setPos(pos);
            return;
        }
        this->setVelocity((pos - m_pos) / dt);
    }
    Body& Body::noneResistanced()
    {
        return this->setAccel({ 0, 0 })
            .setDecelX(0)
            .setMaxSpeed(s3d::none);
    }
    Body& Body::reversed()
    {
        m_forward = m_forward.mirrored();
        return *this;
    }
    Body& Body::addForce(const s3d::Vec2& force)
    {
        m_velocity += force * m_pActor->deltaTime() /*/ mass*/;
    }
    Body& Body::addImpulse(const s3d::Vec2& impulse)
    {
        m_velocity += impulse /*/ mass*/;
    }
    bool Body::isForward(Forward f) const
    {
        return m_forward.isSame(f);
    }
    ColDirection Body::fixPos(const Physics::TerrainData& terrain)
    {
        ColDirection c = terrain.col;
        // 速度による判定無視は、prevRegionと比較しFixPos側で行ってる

        auto selfRegion = this->region();
        s3d::Vec2 before = selfRegion.center();
        
        auto [after, colDir] = FixPos::ByPrevPos(terrain.region, selfRegion, this->prevRegion(), c);

        this->addPos(after - before);

        return colDir;
    }
    ColDirection Body::fixPos(const Room::RoomData& room, const s3d::Optional<ColDirection>& strict)
    {
        auto c = strict.value_or(room.getCol());
        c.ignoreForVelocity(m_velocity);

        s3d::Vec2 before = this->region().center();

        auto [after, colDir] = FixPos::InnerByLatestPos(room.getRegion(), before, c);

        this->addPos(after - before);

        return colDir;
    }
    s3d::Vec2 Body::getCenterPos() const
    {
        return this->getOffsetedPos();
    }
    s3d::Vec2 Body::moveDiff() const
    {
        return m_pos - m_prevPos;
    }
    s3d::RectF Body::region() const
    {
        return { m_pos + m_offset - m_size / 2, m_size };
    }
    s3d::RectF Body::prevRegion() const
    {
        return { m_prevPos + m_offsetPrev - m_sizePrev / 2, m_sizePrev };
    }
}
