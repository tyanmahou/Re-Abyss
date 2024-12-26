#include <abyss/components/Actor/Player/State/DoorInState.hpp>
#include <abyss/components/Actor/Player/State/SwimState.hpp>
#include <abyss/components/Actor/Player/SeDef.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Event/RoomMove/DoorMove/Builder.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    DoorInState::DoorInState(const Gimmick::Door::DoorData& door, const Room::RoomData& room):
        m_door(door),
        m_room(room)
    {}

    void DoorInState::start()
    {
        m_motion->set(Motion::Door);

        // SE
        m_audio->play(SeDef::DoorMove);

        // 攻撃タイマーリセット
        m_attackCtrl->reset();

        // 速度0にする
        m_body->setVelocity(Vec2::Zero());
        m_body->setForward(m_door.getTargetForward());

        // ドア移動
        m_pActor->getModule<Events>()->create<Event::RoomMove::DoorMove::Builder>(
            m_room,
            m_door,
            m_body->getCenterPos(),
            [this]() {
            // ステートを更新する
            auto stateCtrl = m_pActor->find<StateCtrl>();
            stateCtrl->changeState<SwimState>();
            stateCtrl->stateUpdate();
        });

        if (m_door.isSave()) {
            // セーブ対象だった場合
            m_pActor->getModule<Temporary>()->reserveRestartId(m_door.getStartId());
        }
    }
    void DoorInState::end()
    {
        m_motion->set(Motion::Stay);
    }
    void DoorInState::update()
    {
    }
}
