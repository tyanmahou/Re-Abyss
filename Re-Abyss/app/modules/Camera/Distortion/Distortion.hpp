#pragma once
#include <abyss/views/Camera/Distortion/DistortionView.hpp>

namespace abyss
{
    class DistortionView;

    /// <summary>
    /// 歪み
    /// </summary>
    class Distortion
    {
    public:
        void clear();

        void addCircleFrame(const s3d::Circle& circle, double thickness, double power);

        s3d::ScopedCustomShader2D start() const;
    private:
        DistortionView m_view;
    };
}