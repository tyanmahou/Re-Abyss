#pragma once
#include <abyss/views/Actors/Ooparts/base/IDrawCallbackView.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsView;

    class SimpleDrawCallbackView : public IDrawCallbackView
    {
    public:
        SimpleDrawCallbackView(OopartsView* view);
        void onDraw(const s3d::Vec2& pos) const override;
    private:
        OopartsView* m_pView;
        EffectEx m_effect;
        IntervalTimer m_effectTimer;
    };
}