#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Effect
{
    class Drawer final:
        public IComponent,
        public IDraw
    {
    public:
        Drawer(EffectObj* pObj);

        void setLayer(DrawLayer layer)
        {
            m_layer = layer;
        }

        void setOrder(double order)
        {
            m_order = order;
        }
    public:
        void onStart() override;
        void onDraw() const override;

        DrawLayer getLayer() const override
        {
            return m_layer;
        }
        double getOrder() const override
        {
            return m_order;
        }
    private:
        EffectObj* m_pObj;
        s3d::Array<Coro::Task<>> m_drawTasks;

        DrawLayer m_layer = DrawLayer::WorldFront;
        double m_order = 1.0001;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Drawer>
    {
        using Base = Effect::IDraw;
    };
}