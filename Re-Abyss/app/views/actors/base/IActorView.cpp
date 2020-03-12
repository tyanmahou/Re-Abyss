#include "IActorView.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/World/World.hpp>

namespace abyss
{
    IActorView::IActorView(WorldView* const pWorldView) :
        m_pWorldView(pWorldView)
    {}
    IActorView::IActorView(const IActor* const pActor) :
        IActorView(&pActor->getWorld()->getView())
    {}
}
