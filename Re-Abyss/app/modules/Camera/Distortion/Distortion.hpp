#pragma once
#include <abyss/views/Camera/Distortion/DistortionView.hpp>

namespace abyss
{
    /// <summary>
    /// 歪み
    /// </summary>
    class Distortion
    {
    public:
        void clear();

        void addCircleFrame(const s3d::Circle& circle, double thickness, double power);
        void addCircleFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower);

        void render() const;
        s3d::ScopedCustomShader2D start() const;
    private:
        DistortionView m_view;
    };
}