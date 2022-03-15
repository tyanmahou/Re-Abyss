#include <abyss/views/Actor/Enemy/Slime/SlimeVM.hpp>
#include <Siv3D.hpp>
#include <abyss/params/Actor/Enemy/Slime/Param.hpp>

namespace abyss::Actor::Enemy::Slime
{
    SlimeVM::SlimeVM(Resource::Assets* asset):
        m_texture(asset->load(U"Actor/Enemy/Slime/Slime.png"))
    {}
    SlimeVM& SlimeVM::setTime(double time)
    {
        m_time = time;
        return *this;
    }
    SlimeVM& SlimeVM::setForward(const Forward & forward)
    {
        m_forward = forward;
        return *this;
    }
    SlimeVM& SlimeVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = Math::Round(pos);
        return *this;
    }
    SlimeVM& SlimeVM::setVelocity(const s3d::Vec2& velocity)
    {
        m_velocity = velocity;
        return *this;
    }

    SlimeVM& SlimeVM::setColorMul(const s3d::ColorF color)
    {
        m_colorMul = color;
        return *this;
    }

    void SlimeVM::draw() const
    {
        switch (m_motion) {
        case Motion::Walk:
            this->drawWalk();
            break;
        case Motion::Jump:
            this->drawJump();
        default:
            break;
        }
    }

    void SlimeVM::drawWalk() const
    {
        bool isLeft = m_forward == Forward::Left;
        int32 time = static_cast<int32>(Periodic::Square0_1(Param::View::WalkAnimeTimeSec, m_time));
        auto tex = m_texture(40 * time, 0, 40, 40);
        (isLeft ? tex : tex.mirrored()).drawAt(m_pos, m_colorMul);
    }

    void SlimeVM::drawJump() const
    {
        bool isLeft = m_forward == Forward::Left;

        int32 page = m_velocity.y > 0 ? 1 : 0;
        auto tex = m_texture(40 * page, 40, 40, 40);
        (isLeft ? tex : tex.mirrored()).drawAt(m_pos, m_colorMul);
    }

}
