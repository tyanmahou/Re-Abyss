#pragma once
#include "IDrawCallbackView.hpp"

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Ooparts
{
    class ActDrawCallbackView : public IDrawCallbackView
    {
        IntervalTimer m_effectTimer;
        Manager* m_pManager;
    public:
        void onDraw(const s3d::Vec2& pos) const final;
    };
}