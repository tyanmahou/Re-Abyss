#include <abyss/components/Actor/Gimmick/Door/GimmickReactor.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Player/State/DoorInState.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::Actor::Gimmick::Door
{
    GimmickReactor::GimmickReactor(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void GimmickReactor::onStart()
    {
        m_door = m_pActor->find<DoorProxy>();
        m_collider = m_pActor->find<Collider>()->main();
    }
    void GimmickReactor::onGimmickReact(ActorObj * player)
    {
        auto playerCollider = player->find<Collider>()->main();
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
