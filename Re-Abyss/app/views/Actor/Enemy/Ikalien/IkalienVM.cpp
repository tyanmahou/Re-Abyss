#include <abyss/views/Actor/Enemy/Ikalien/IkalienVM.hpp>
#include <Siv3D.hpp>
#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    IkalienVM::IkalienVM():
        m_texture(Resource::Assets::Main()->load(U"Actor/Enemy/Ikalien/Ikalien.png"))
    {}
    IkalienVM& IkalienVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    IkalienVM& IkalienVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = s3d::Round(pos);
        return *this;
    }

    IkalienVM& IkalienVM::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        return *this;
    }

    IkalienVM& IkalienVM::setRotate(double rotate)
    {
        m_rotate = rotate;
        return *this;
    }
    IkalienVM& IkalienVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }
    void IkalienVM::draw() const
    {
        switch (m_motion) {
        case Motion::Wait:
            this->drawWait();
            break;
        case Motion::Swim:
            this->drawSwim();
            break;
        case Motion::Pursuit:
            this->drawPursuit();
            break;
        default:
            break;
        }
    }

    void IkalienVM::drawWait() const
    {
        int32 page = static_cast<int32>(Periodic::Triangle0_1(Param::View::WaitAnimeTimeSec, m_time) * 4.0);
        auto tex = m_texture(80 * page, 80, 80, 80);
        tex.rotated(m_rotate).drawAt(m_pos, m_colorMul);
    }

    void IkalienVM::drawPursuit() const
    {
        this->drawWait();
    }

    void IkalienVM::drawSwim() const
    {
        int32 page = 0;
        double velocityLen = m_velocity.length();
        if (velocityLen >= 300) {
            page = 3;
        } else if(velocityLen >= 280) {
            page = 2;
        } else if (velocityLen >= 260) {
            page = 1;
        }
        auto tex = m_texture(80 * page, 0, 80, 80);
        tex.rotated(m_rotate).drawAt(m_pos, m_colorMul);
    }

}
