#include "SwimState.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Map/PenetrateFloor/PenetrateFloorActor.hpp>
#include <abyss/controllers/Actors/Map/Ladder/LadderActor.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/controllers/Actors/Gimmick/Door/DoorActor.hpp>
#include <abyss/controllers/Save/Save.hpp>
#include <abyss/controllers/Event/RoomMove/DoorMove/DoorMove.hpp>

namespace abyss::Player
{
    void SwimState::onLanding()
    {
        if (m_motion == Motion::Float && m_body->getVelocity().x == 0) {
            m_motion = Motion::Stay;
        } else if (m_motion == Motion::Swim && Abs(m_body->getVelocity().x) > 90) {
            m_motion = Motion::Run;
        }
    }
    void SwimState::onCollisionStay(const PenetrateFloorActor& col)
    {
        if (m_mapCol->isHitGround() &&
            col.tryDown(m_body->region()) &&
            InputManager::Down.down()
            ) {
            // 降りる
            m_body->addPosY(10.0);
        }
    }

    void SwimState::onCollisionStay(const DoorActor & col)
    {
        if (InputManager::Up.down()) {
            m_motion = Motion::Door;
            m_body->setVelocity(Vec2::Zero());
            m_body->setForward(col.getTargetForward());
            Event::RoomMove::DoorMove::Start(col, m_body->getPos(), [this]() {
                this->m_motion = Motion::Stay;
            });
            m_pActor->find<AudioSourceModel>()->play(U"DoorMove");
            if (col.isSave()) {
                // セーブ対象だった場合
                m_pActor->getModule<Save>()->reserveRestartId(col.getStartId());
            }
        }
    }
    void SwimState::start()
    {
        BaseState::start();
    }
    void SwimState::update(double dt)
    {
        BaseState::update(dt);

        m_motion = Motion::Float;
        if (InputManager::Left.pressed() || InputManager::Right.pressed()) {
            m_motion = Motion::Swim;
        }
        if (m_body->getVelocity().y > BodyModel::DefaultMaxVelocityY) {
            m_motion = Motion::Dive;
        }
    }
    void SwimState::lastUpdate([[maybe_unused]]double dt)
    {
        BaseState::lastUpdate(dt);

        if (m_foot->isLadder()) {
            bool canUp = !m_foot->isLadderTop() && InputManager::Up.down();
            bool canDown = (m_foot->isLadderTop() || !m_foot->isLanding()) && InputManager::Down.down();
            
            if (canUp || canDown) {
                m_body->setPosX(*m_foot->getLadderPosX());
                m_body->addPosY(-2 * (canUp - canDown));
                this->changeState(State::Ladder);
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