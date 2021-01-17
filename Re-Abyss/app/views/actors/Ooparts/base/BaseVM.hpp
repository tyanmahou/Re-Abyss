#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Ooparts
{
    class BaseVM
    {
    protected:
        s3d::Vec2 m_pos{ 0, 0 };
        Forward m_forward{ Forward::Right };
        double m_time = 0;
    public:

        BaseVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        double getTime() const
        {
            return m_time;
        }
        BaseVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        BaseVM& setForward(Forward forward)
        {
            m_forward = forward;
            return *this;
        }
        virtual void draw(const s3d::ColorF& color = s3d::Palette::White) const = 0;
        virtual s3d::TextureRegion icon() const = 0;
    };
}