#pragma once
#include <abyss/modules/DrawManager/DrawLayer.hpp>
namespace abyss::Decor
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
        IDraw& setLayer(DrawLayer layer)
        {
            m_layer = layer;
            return *this;
        }
        double getOrder() const
        {
            return m_order;
        }
        IDraw& setOrder(double order)
        {
            m_order = order;
            return *this;
        }
    private:
        DrawLayer m_layer = DrawLayer::DecorBack;
        double m_order = 1.0;
    };
}