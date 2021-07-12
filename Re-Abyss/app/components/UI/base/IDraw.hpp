#pragma once
#include <abyss/modules/DrawManager/DrawLayer.hpp>

namespace abyss::UI
{
    class IDraw
    {
    public:
        virtual ~IDraw() = default;
        virtual void onDraw()const = 0;

        DrawLayer getLayer() const
        {
            return m_layer;
        }
        void setLayer(DrawLayer layer)
        {
            m_layer = layer;
        }

    private:
        DrawLayer m_layer = DrawLayer::UI;
    };
}