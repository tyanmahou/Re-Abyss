#pragma once
#include <functional>

#include <abyss/views/Camera/Distortion/DistortionShader.hpp>

#include <Siv3D/Array.hpp>
#include <Siv3D/RenderTexture.hpp>

namespace abyss
{
    class DistortionView
    {
    public:
        DistortionView();

        void clear();

        void addCircle(const s3d::Circle& circle, double power);
        void addCircle(const s3d::Circle& circle, double innerPower, double outerPower);

        void addCircleFrame(const s3d::Circle& circle, double thickness, double power);
        void addCircleFrame(const s3d::Circle& circle, double innerThickness, double outerThickness, double innerPower, double outerPower);

        void render() const;
        s3d::ScopedCustomShader2D start() const;
    private:
        s3d::RenderTexture m_rt;
        DistortionShader m_shader;
        s3d::Array<std::function<void()>> m_drawer;
    };
}