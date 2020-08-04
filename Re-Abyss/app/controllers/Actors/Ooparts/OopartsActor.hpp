#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Ooparts
{
    class OopartsVM;

    class OopartsActor:
        public IActor
    {
    protected:
        Ref<ViewModel<OopartsVM>> m_view;

    public:
        OopartsActor(IActor* parent);
    };
}