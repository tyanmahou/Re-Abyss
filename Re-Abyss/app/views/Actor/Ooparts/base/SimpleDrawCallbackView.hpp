#pragma once
#include <abyss/views/Actor/Ooparts/base/IDrawCallbackView.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/EffectEx/EffectEx.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsView;

    class SimpleDrawCallbackView : public IDrawCallbackView
    {
    public:
        SimpleDrawCallbackView(Clock_t clock);
        void update() const;
        void onAddEffect(std::unique_ptr<s3d::IEffect>&& effect) const override;
    private:
        EffectEx m_effect;
    };
}