#include "GimmickReacter.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/base/ICollider.hpp>
#include <abyss/components/Actors/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Player/State/DoorInState.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

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
        auto playerCollider = player->find<ICollider>();
        if (m_collider && playerCollider) {
            // 衝突してないならスルーする
            if (!ColisionUtil::Intersects(playerCollider->getCollider(), m_collider->getCollider())) {
                return;
            }
        }
        if (!player->find<Player::StateChecker>()->canDoorState()) {
            // ドア移動可能ステートじゃないならスルー
            return;
        }
        if (InputManager::Up.down()) {
            player->find<StateCtrl>()->changeState<Player::DoorInState>(m_door);
        }
    }
}
