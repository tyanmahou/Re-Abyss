#pragma once
#include <abyss/views/Actor/Ooparts/base/IDrawCallbackView.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/IntervalTimer/IntervalTimer.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsView;

    class ActDrawCallbackView : public IDrawCallbackView
    {
        Manager* m_pManager;
    public:
        ActDrawCallbackView(Manager* manager);

        void onAddEffect(std::unique_ptr<s3d::IEffect>&& effect) const final;
    };
}