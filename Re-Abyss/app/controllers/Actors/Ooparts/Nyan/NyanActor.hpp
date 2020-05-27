#pragma once
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>
#include <abyss/views/Actors/Ooparts/Xto/XtoVM.hpp>

namespace abyss::Ooparts::Nyan
{
    class NyanVM;

    class NyanActor :
        public OopartsActor
    {
        std::shared_ptr<NyanVM> m_view;
    public:
        NyanActor(IActor* parent);

        OopartsVM* getBindedView() const override;
    };
}