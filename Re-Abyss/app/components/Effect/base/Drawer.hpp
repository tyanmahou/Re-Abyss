#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Effect
{
    class Drawer final: public IComponent
    {
    public:
        Drawer(EffectObj* pObj);

        void onStart() override;
        void draw() const;

        DrawLayer getLayer() const
        {
            return m_layer;
        }
        void setLayer(DrawLayer layer)
        {
            m_layer = layer;
        }
        double getOrder() const
        {
            return m_order;
        }
        void setOrder(double order)
        {
            m_order = order;
        }
    private:
        EffectObj* m_pObj;
        s3d::Array<Coro::Task<>> m_drawTasks;

        DrawLayer m_layer = DrawLayer::WorldFront;
        double m_order = 1.0001;
    };
}