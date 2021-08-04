#pragma once

#include <abyss/views/BackGround/BackGroundView.hpp>
#include <abyss/views/Env/WaterSurface/WaterSurfaceView.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class BackGround
    {
    private:
        BackGroundView m_view;
        Env::WaterSurfaceView m_waterSarface;
    public:
        BackGround() = default;

        void update(double time);

        void add(const BackGroundVM& backGround);
        void setBgColor(const s3d::ColorF& color);
        const s3d::ColorF& getBgColor() const;
        void draw(const CameraView& camera) const;
        void drawWaterSurfaceBack(const CameraView& camera) const;
        void drawWaterSurfaceFront(const CameraView& camera) const;
    };
}