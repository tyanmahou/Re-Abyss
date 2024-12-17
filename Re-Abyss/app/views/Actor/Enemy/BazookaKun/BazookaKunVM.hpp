#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class BazookaKunVM
    {
    public:
        BazookaKunVM();

        BazookaKunVM& setPos(const s3d::Vec2& pos);
        BazookaKunVM& setCenterPos(const s3d::Vec2& pos);
        BazookaKunVM& setIsMirrored(bool isMirrored)
        {
            m_isMirrored = isMirrored;
            return *this;
        }
        BazookaKunVM& setIsFlipped(bool isFlipped)
        {
            m_isFlipped = isFlipped;
            return *this;
        }
        BazookaKunVM& setRotate(double rotate)
        {
            m_rotate = rotate;
            return *this;
        }
        BazookaKunVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        BazookaKunVM& setColorMul(const s3d::ColorF color);

        BazookaKunVM& setBazookaRotate(double rotate)
        {
            m_bazookaRotate = rotate;
            return *this;
        }
        BazookaKunVM& setBazookaAnimRate(double rate)
        {
            m_bazookaAnimRate = rate;
            return *this;
        }
        void draw() const;
    private:
        s3d::RectF rect() const;
        s3d::Quad quad() const;
        void drawBazooka() const;
        void drawBody() const;
        void drawEye() const;
    private:
        TexturePacker m_texture;

        s3d::Vec2 m_pos{};
        s3d::Vec2 m_centerPos{};
        bool m_isMirrored;
        bool m_isFlipped;
        double m_rotate;
        double m_time = 0;

        double m_bazookaRotate = 0;
        double m_bazookaAnimRate = 0;

        s3d::ColorF m_colorMul;
    };
}
