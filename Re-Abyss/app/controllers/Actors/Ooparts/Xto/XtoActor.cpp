#include "XtoActor.hpp"
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/views/Actors/Ooparts/Xto/XtoVM.hpp>

namespace abyss::Ooparts::Xto
{
    XtoActor::XtoActor(IActor* parent):
        OopartsActor(parent),
        m_view(std::make_shared<XtoVM>())
    {}

    OopartsVM* XtoActor::getBindedView() const
    {
        return  &m_view
            ->setTime(this->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setForward(m_body->getForward())
            ;
    }
}
