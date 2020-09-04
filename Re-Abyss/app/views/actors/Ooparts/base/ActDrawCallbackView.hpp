#pragma once
#include <abyss/views/Actors/Ooparts/base/IDrawCallbackView.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Ooparts
{
    class OopartsVM;

    class ActDrawCallbackView : public IDrawCallbackView
    {
        OopartsVM* m_pView;

        IntervalTimer m_effectTimer;
        Manager* m_pManager;
    public:
        ActDrawCallbackView(OopartsVM* view, Manager* manager);

        void onDraw(const s3d::Vec2& pos) const final;
    };
}