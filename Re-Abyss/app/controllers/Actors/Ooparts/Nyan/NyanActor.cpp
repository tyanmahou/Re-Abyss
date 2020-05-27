#include "NyanActor.hpp"
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/views/Actors/Ooparts/Nyan/NyanVM.hpp>

namespace abyss::Ooparts::Nyan
{
    abyss::Ooparts::Nyan::NyanActor::NyanActor(IActor* parent):
        OopartsActor(parent),
        m_view(std::make_shared<NyanVM>())
    {}

    OopartsVM* abyss::Ooparts::Nyan::NyanActor::getBindedView() const
    {
        return  &m_view
            ->setTime(this->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setForward(m_body->getForward())
            ;
    }
}
