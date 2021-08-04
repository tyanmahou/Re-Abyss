#pragma once
#include <abyss/views/Env/WaterSurface/WaterSurfaceView.hpp>

namespace abyss::Env
{
    class WaterSurface
    {
    public:
        void update(double dt);
        void drawBack(const s3d::Vec2& pos) const;
        void drawFront(const s3d::Vec2& pos) const;
    private:
        double m_time = 0.0;
        WaterSurfaceView m_view;
    };
}