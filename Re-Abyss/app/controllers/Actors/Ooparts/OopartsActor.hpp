#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Ooparts
{
    class OopartsVM;

    class OopartsActor:
        public IActor
    {
    protected:
        Ref<ViewCtrl<OopartsVM>> m_view;

    public:
        OopartsActor(IActor* parent);
    };
}