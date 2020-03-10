#include "IActorView.hpp"
#include <abyss/models/actors/base/IActor.hpp>
#include <abyss/models/World/WorldModel.hpp>

namespace abyss
{
    IActorView::IActorView(WorldView* const pWorldView) :
        m_pWorldView(pWorldView)
    {}
    IActorView::IActorView(const IActor* const pActor) :
        IActorView(&pActor->getWorld()->getView())
    {}
}
