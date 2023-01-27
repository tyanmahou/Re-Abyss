#pragma once
#include <abyss/modules/Actor/base/IDraw.hpp>
namespace abyss::Actor
{
    class DrawBase : public IDraw
    {
    public:
        DrawLayer getLayer() const override
        {
            return m_layer;
        }
        DrawBase& setLayer(DrawLayer layer)
        {
            m_layer = layer;
            return *this;
        }
        double getOrder() const override
        {
            return m_order;
        }
        DrawBase& setOrder(double order)
        {
            m_order = order;
            return *this;
        }
    private:
        DrawLayer m_layer = DrawLayer::World;
        double m_order = DrawOrder::World::Default;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Actor::DrawBase>
    {
        using Base = Actor::IDraw;
    };
}