#pragma once
#include <abyss/views/Env/WaterSarface/WaterSarfaceView.hpp>

namespace abyss::Env
{
    class WaterSarface
    {
    public:
        void update(double dt);
        void drawBack(const s3d::Vec2& pos) const;
        void drawFront(const s3d::Vec2& pos) const;
    private:
        double m_time = 0.0;
        WaterSarfaceView m_view;
    };
}