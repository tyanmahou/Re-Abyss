#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class BazookaKunVM
    {
    public:
        BazookaKunVM();

        BazookaKunVM& setPos(const s3d::Vec2& pos);
        BazookaKunVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        BazookaKunVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        void draw() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos{};
        Forward m_forward = Forward::Left;
        double m_time = 0;
    };
}
