#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/Effect/base/EffectLayer.hpp>

namespace abyss::Effect
{
    class Drawer;

    class EffectObj final : public GameObject
    {
    public:
        EffectObj();

        void updateDeltaTime(double dt) const;
        double deltaTime() const;
        double updateTimeSec() const;
        double drawTimeSec() const;

        void setTimeScale(double scale);

        void update();
        void draw();

        DrawLayer getLayer() const
        {
            return m_layer;
        }
        void setLayer(DrawLayer layer)
        {
            m_layer = layer;
        }

    private:
        Ref<ClockCtrl> m_clock;
        Ref<Drawer> m_drawer;
        DrawLayer m_layer = EffectLayer::WorldFront;
    };
}