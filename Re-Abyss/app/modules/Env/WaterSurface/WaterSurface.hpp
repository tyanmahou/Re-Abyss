#pragma once
#include <abyss/views/Env/WaterSurface/WaterSurfaceView.hpp>

namespace abyss::Env
{
    class WaterSurface
    {
        enum ActiveState : s3d::uint8
        {
            Back = 0x01,
            Front = 0x02,

            All = Back | Front,
        };
    public:
        void update(double dt);
        void setActiveBack(bool isActive);
        void setActiveFront(bool isActive);

        void drawBack(const s3d::Vec2& pos) const;
        void drawFront(const s3d::Vec2& pos) const;
    private:
        double m_time = 0.0;
        WaterSurfaceView m_view;
        s3d::uint8 m_activeState = ActiveState::All;
    };
}