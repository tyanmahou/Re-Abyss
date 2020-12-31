#include "DoorInState.hpp"
#include "SwimState.hpp"

#include <abyss/modules/Save/Save.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Events/RoomMove/DoorMove/Builder.hpp>

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
        m_attackCtrl->reset();
        m_body->setVelocity(Vec2::Zero());
        m_body->setForward(m_door->getTargetForward());

        m_pActor->getModule<Events>()->create<Event::RoomMove::DoorMove::Builder>(
            m_door->getNextRoom(),
            m_door->getDoor(),
            m_body->getPos(),
            [this]() {
            this->changeState<SwimState>();
        });

        m_pActor->find<AudioSource>()->play(U"DoorMove");
        if (m_door->isSave()) {
            // セーブ対象だった場合
            m_pActor->getModule<Save>()->reserveRestartId(m_door->getStartId());
        }

        co_return;
    }
    void DoorInState::update()
    {
        this->onMove(m_pActor->deltaTime());
    }
    void DoorInState::onDraw(const PlayerVM & view) const
    {
        view.drawStateDoor();
    }
}
