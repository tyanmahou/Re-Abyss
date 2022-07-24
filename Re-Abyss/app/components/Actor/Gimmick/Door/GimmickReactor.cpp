#include <abyss/components/Actor/Gimmick/Door/GimmickReactor.hpp>

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Stage/Stage.hpp>

#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>
#include <abyss/components/Actor/Common/StateCtrl.hpp>
#include <abyss/components/Actor/Player/State/DoorInState.hpp>
#include <abyss/components/Actor/Player/State/DoorInMapMoveState.hpp>
#include <abyss/utils/Collision/CollisionUtil.hpp>
#include <abyss/debugs/Debug.hpp>

namespace abyss::Actor::Gimmick::Door
{
    GimmickReactor::GimmickReactor(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    void GimmickReactor::onStart()
    {
        m_door = m_pActor->find<DoorProxy>();
        m_collider = m_pActor->find<Collider>()->main();
    }
    void GimmickReactor::onGimmickReact(ActorObj* player)
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
            auto pStage = m_pActor->getModule<Stage>();
            if (const auto& link = m_door->getLink()) {
                Door::DoorData door{
                    m_door->getStartId(),
                    m_door->getPos(),
                    {},
                    {},
                    m_door->getSize(),
                    m_door->getKind(),
                    true
                };
                Player::DoorInMapMoveState::Change(player, door, *link);
                return;
            } else if (auto startPos = pStage->findStartPos(m_door->getStartId())) {
                if (auto room = pStage->findRoom(startPos->getPos())) {
                    Door::DoorData door{
                        startPos->getStartId(),
                        m_door->getPos(),
                        startPos->getPos(),
                        startPos->getForward(),
                        m_door->getSize(),
                        m_door->getKind(),
                        startPos->isSave()
                    };
                    player->find<StateCtrl>()->changeState<Player::DoorInState>(door, *room);
                    return;
                }
            }
#if ABYSS_DEBUG
            Debug::Log::Warn(U"Not Found Door dest (startId: {})"_fmt(m_door->getStartId()));
#endif
        }
    }
}
