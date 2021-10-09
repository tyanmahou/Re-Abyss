#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/DrawManager/DrawLayer.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Ooparts
{
    class KiraKiraAlgorithm
    {
    public:
        KiraKiraAlgorithm(Effects* effects, DrawLayer layer);

        void update(
            const s3d::Vec2& pos,
            double dt,
            std::function<void(Effect::EffectObj*)> callback = nullptr
        );
    private:
        Effects* m_effects;
        DrawLayer m_layer;
        TimeLite::IntervalTimer m_intervalTimer;
    };
}