#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

namespace abyss::Effect
{
    class Drawer;

    class EffectObj final : public GameObject
    {
    public:
        EffectObj();

        void updateDeltaTime(double dt) const;
        double deltaTime() const;
        double timeSec() const;

        void setTimeScale(double scale);

        void update();
        void draw();

        DrawLayer getLayer() const;
        EffectObj& setLayer(DrawLayer layer);

        double getOrder() const;
        EffectObj& setOrder(double order);
    private:
        Ref<ClockCtrl> m_clock;
        Ref<Drawer> m_drawer;
    };
}