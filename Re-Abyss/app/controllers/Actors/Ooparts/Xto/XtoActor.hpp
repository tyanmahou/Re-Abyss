#pragma once
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>
#include <abyss/views/Actors/Ooparts/Xto/XtoVM.hpp>

namespace abyss::Ooparts::Xto
{
    class XtoVM;

    class XtoActor :
        public OopartsActor
    {
        std::shared_ptr<XtoVM> m_view;
    public:
        XtoActor(IActor* parent);

        OopartsVM* getBindedView() const override;
    };
}