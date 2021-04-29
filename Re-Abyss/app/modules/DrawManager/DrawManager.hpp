#pragma once
#include <functional>
#include <array>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class DrawManager
    {
        std::array<s3d::Array<std::function<void()>>, DrawLayerSize> m_drawers;
    };
}