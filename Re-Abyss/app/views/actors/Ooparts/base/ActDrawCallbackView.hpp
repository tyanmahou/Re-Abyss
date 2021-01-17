#pragma once
#include <abyss/views/Actors/Ooparts/base/IDrawCallbackView.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsView;

    class ActDrawCallbackView : public IDrawCallbackView
    {
        OopartsView* m_pView;

        IntervalTimer m_effectTimer;
        Manager* m_pManager;
    public:
        ActDrawCallbackView(OopartsView* view, Manager* manager);

        void onDraw(const s3d::Vec2& pos) const final;
    };
}