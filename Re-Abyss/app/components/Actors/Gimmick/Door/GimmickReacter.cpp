#include "GimmickReacter.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>

namespace abyss::Actor::Gimmick::Door
{
    GimmickReacter::GimmickReacter(IActor* pActor):
        m_pActor(pActor)
    {}
    void GimmickReacter::onStart()
    {
        m_door = m_pActor->find<DoorProxy>();
        m_collider = m_pActor->find<ICollider>();
    }
    void GimmickReacter::onGimmickReact(IActor * player)
    {

    }
}
