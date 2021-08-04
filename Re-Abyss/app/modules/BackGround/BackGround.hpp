#pragma once

#include <abyss/views/BackGround/BackGroundView.hpp>
#include <abyss/views/Env/WaterSarface/WaterSarfaceView.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class BackGround
    {
    private:
        BackGroundView m_view;
        Env::WaterSarfaceView m_waterSarface;
    public:
        BackGround() = default;

        void update(double time);

        void add(const BackGroundVM& backGround);
        void setBgColor(const s3d::ColorF& color);
        const s3d::ColorF& getBgColor() const;
        void draw(const CameraView& camera) const;
        void drawWaterSarfaceBack(const CameraView& camera) const;
        void drawWaterSarfaceFront(const CameraView& camera) const;
    };
}