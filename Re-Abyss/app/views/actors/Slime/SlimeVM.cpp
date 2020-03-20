#include "SlimeVM.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>
namespace abyss
{
    SlimeVM::SlimeVM():
        m_texture(U"work/enemy/slime/slime.png")
    {}
    void SlimeVM::bind(const SlimeActor & actor)
    {
        m_forward = actor.getForward();
        m_pos = actor.getPos();
        m_velocity = actor.getVellocity();
    }
    void SlimeVM::drawWalk() const
    {
        bool isLeft = m_forward == Forward::Left;
        int32 time = static_cast<int32>(Periodic::Square0_1(1s));
        auto tex = m_texture(40 * time, 0, 40, 40);
        (isLeft ? tex : tex.mirrored()).drawAt(m_pos);
    }

    void SlimeVM::drawJump() const
    {
        bool isLeft = m_forward == Forward::Left;

        int32 page = m_velocity.y > 0 ? 1 : 0;
        auto tex = m_texture(40 * page, 40, 40, 40);
        (isLeft ? tex : tex.mirrored()).drawAt(m_pos);
    }

}
