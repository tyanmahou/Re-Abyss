#pragma once
#include <functional>
#include <Siv3D/Array.hpp>

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
    private:
        s3d::Array<std::function<void()>> m_drawer;
    };
}