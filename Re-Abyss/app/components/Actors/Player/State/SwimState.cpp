#include "SwimState.hpp"
#include "LadderState.hpp"

#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/System/System.hpp>
#include <abyss/modules/Save/Save.hpp>
#include <abyss/components/Events/RoomMove/DoorMove/Builder.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    void SwimState::onLanding()
    {
        if (m_motion == Motion::Float && m_body->getVelocity().x == 0) {
            m_motion = Motion::Stay;
        } else if (m_motion == Motion::Swim && Abs(m_body->getVelocity().x) > 90) {
            m_motion = Motion::Run;
        }
    }
    bool SwimState::onCollisionStay(const PenetrateFloorProxy& col)
    {
        if (m_mapCol->isHitGround() &&
            col.tryDown(m_body->region()) &&
            InputManager::Down.down()
            ) {
            // 降りる
            m_body->addPosY(10.0);
        }
        return false;
    }

    bool SwimState::onCollisionStay(const DoorProxy& col)
    {
        if (InputManager::Up.down()) {
            m_motion = Motion::Door;
            m_attackCtrl->reset();
            m_body->setVelocity(Vec2::Zero());
            m_body->setForward(col.getTargetForward());

            m_pActor->getModule<Events>()->create<Event::RoomMove::DoorMove::Builder>(
                col.getNextRoom(),
                col.getDoor(),
                m_body->getPos(),
                [this]() {
                    this->m_motion = Motion::Stay;
                });

            m_pActor->find<AudioSource>()->play(U"DoorMove");
            if (col.isSave()) {
                // セーブ対象だった場合
                m_pActor->getModule<Save>()->reserveRestartId(col.getStartId());
            }
            return true;
        }
        return false;
    }
    Task<> SwimState::start()
    {
        co_yield BaseState::start();
    }
    void SwimState::update()
    {
        BaseState::update();

        m_motion = Motion::Float;
        if (InputManager::Left.pressed() || InputManager::Right.pressed()) {
            m_motion = Motion::Swim;
        }
        if (m_body->getVelocity().y > Body::DefaultMaxVelocityY) {
            m_motion = Motion::Dive;
        }
    }
    void SwimState::lastUpdate()
    {
        BaseState::lastUpdate();

        if (m_foot->isLadder()) {
            bool canUp = !m_foot->isLadderTop() && InputManager::Up.down();
            bool canDown = (m_foot->isLadderTop() || !m_foot->isLanding()) && InputManager::Down.down();
            
            if (canUp || canDown) {
                m_body->setPosX(*m_foot->getLadderPosX());
                m_body->addPosY(-2 * (canUp - canDown));
                this->changeState<LadderState>();
                m_motion = Motion::Ladder;
            }
        }
    }
    void SwimState::onDraw(const PlayerVM& view) const
    {
        switch (m_motion) {
        case Motion::Stay: return view.drawStateStay();
        case Motion::Swim: return view.drawStateSwim();
        case Motion::Run: return view.drawStateRun();
        case Motion::Float: return view.drawStateFloat();
        case Motion::Dive: return view.drawStateDive();
        case Motion::Door: return view.drawStateDoor();
        case Motion::Ladder: return view.drawStateLadder();
        default:
            break;
        }
    }
}