#pragma once

#include <abyss/views/BackGround/BackGroundView.hpp>
#include <abyss/views/BackGround/WaterSarface/WaterSarfaceView.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class BackGround
    {
    private:
        BackGroundView m_view;
        WaterSarfaceView m_waterSarface;
    public:
        BackGround() = default;

        void add(const BackGroundVM& backGround);
        void draw(const CameraView& camera) const;
        void drawWaterSarfaceBack(const CameraView& camera) const;
        void drawWaterSarfaceFront(const CameraView& camera) const;
    };
}