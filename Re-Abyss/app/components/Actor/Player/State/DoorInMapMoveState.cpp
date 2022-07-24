#include <abyss/components/Actor/Player/State/DoorInMapMoveState.hpp>

#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Event/MapMove/DoorIn/Builder.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    void DoorInMapMoveState::Change(ActorObj* player, const Gimmick::Door::DoorData& door, const s3d::String& link)
    {
        player->find<StateCtrl>()->changeState<DoorInMapMoveState>(door, link);
    }
    DoorInMapMoveState::DoorInMapMoveState(
        const Gimmick::Door::DoorData& door,
        const s3d::String& link
    ):
        m_door(door),
        m_link(link)
    {
    }
    void DoorInMapMoveState::start()
    {
        m_motion->set(Motion::Door);

        // SE
        m_audio->play(U"DoorMove");

        // 攻撃タイマーリセット
        m_attackCtrl->reset();

        // 速度0にする
        m_body->setVelocity(Vec2::Zero());

        // ドア移動
        m_pActor->getModule<Events>()->create<Event::MapMove::DoorIn::Builder>(
            m_door,
            m_link,
            m_body->getPos()
            );
    }
    void DoorInMapMoveState::end()
    {
    }
    void DoorInMapMoveState::update()
    {
    }
}
