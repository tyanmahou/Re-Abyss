#pragma once
#include <functional>
#include <array>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class DrawManager
    {
    public:
        void clear();
        void add(DrawLayer layer, std::function<void()> drawer);
    private:
        std::array<s3d::Array<std::function<void()>>, DrawLayerSize> m_drawers;
    };
}