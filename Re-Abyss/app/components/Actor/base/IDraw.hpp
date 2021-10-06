#pragma once
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <abyss/modules/DrawManager/DrawOrder.hpp>

namespace abyss::Actor
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
        DrawLayer m_layer = DrawLayer::World;
        double m_order = DrawOrder::World::Default;
    };
}