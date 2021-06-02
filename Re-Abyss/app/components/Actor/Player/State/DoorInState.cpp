#include "DoorInState.hpp"
#include "SwimState.hpp"

#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Event/RoomMove/DoorMove/Builder.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    DoorInState::DoorInState(const Ref<Gimmick::Door::DoorProxy>& door):
        m_door(door)
    {}

    Task<> DoorInState::start()
    {
        if (!m_door) {
            this->changeState<SwimState>();
        }

        // SE
        m_pActor->find<AudioSource>()->play(U"DoorMove");

        // 攻撃タイマーリセット
        m_attackCtrl->reset();

        // 速度0にする
        m_body->setVelocity(Vec2::Zero());
        m_body->setForward(m_door->getTargetForward());

        // ドア移動
        m_pActor->getModule<Events>()->create<Event::RoomMove::DoorMove::Builder>(
            m_door->getNextRoom(),
            m_door->getDoor(),
            m_body->getPos(),
            [this]() {
            // ステートを更新する
            auto stateCtrl = m_pActor->find<StateCtrl>();
            stateCtrl->changeState<SwimState>();
            stateCtrl->stateUpdate();
        });

        if (m_door->isSave()) {
            // セーブ対象だった場合
            m_pActor->getModule<Temporary>()->reserveRestartId(m_door->getStartId());
        }

        co_return;
    }
    void DoorInState::update()
    {
    }
    void DoorInState::onDraw(const PlayerVM & view) const
    {
        view.drawStateDoor();
    }
}
