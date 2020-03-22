#include "PlayerSwimState.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/PenetrateFloor/PenetrateFloorActor.hpp>
#include <abyss/controllers/Actors/Ladder/LadderActor.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
namespace abyss
{
    void PlayerSwimState::onLanding()
    {
        if (m_motion == Motion::Float && m_body->getVelocity().x == 0) {
            m_motion = Motion::Stay;
        } else if (m_motion == Motion::Swim && Abs(m_body->getVelocity().x) > 90) {
            m_motion = Motion::Run;
        }
    }
    void PlayerSwimState::onCollisionStay(const PenetrateFloorActor& col)
    {
        auto colDir = this->fixPos(col.getMapColInfo());

        if (colDir.isUp() &&
            col.tryDown(m_body->region()) &&
            InputManager::Down.down()
            ) {
            // 降りる
            m_body->addPosY(10.0);
        }
    }
    void PlayerSwimState::onCollisionStay(const LadderActor & ladder)
    {
        if (ladder.isTop()) {
            this->fixPos(ladder.getMapColInfo());
        }
        if (ladder.getCenterLine().intersects(m_body->region())) {
            if (!ladder.isTop() && InputManager::Up.down() || InputManager::Down.down()) {
                // 上下押した
                m_body->setPosX(ladder.getPos().x);
                m_body->addPosY(-2 * (InputManager::Up.down() - InputManager::Down.down()));
                this->changeState(PlayerActor::State::Ladder);
            }
        }
    }
    void PlayerSwimState::onCollisionStay(const DoorActor & col)
    {
        if (InputManager::Up.down()) {
            m_motion = Motion::Door;
            m_body->setVelocity(Vec2::Zero());
            ActionSystem::Camera()->startDoorCameraWork(col, m_body->getPos(), [this]() {
                this->m_motion = Motion::Stay;
            });
        }
    }
    void PlayerSwimState::start()
    {
        PlayerBaseState::start();
    }
    void PlayerSwimState::update(double dt)
    {
        PlayerBaseState::update(dt);

        m_motion = Motion::Float;
        if (InputManager::Left.pressed() || InputManager::Right.pressed()) {
            m_motion = Motion::Swim;
        }
        if (m_body->getVelocity().y > Constants::Player::MaxGravity * 60) {
            m_motion = Motion::Dive;
        }
    }
    void PlayerSwimState::onDraw(const PlayerVM& view) const
    {
        switch (m_motion) {
        case Motion::Stay: return view.drawStateStay();
        case Motion::Swim: return view.drawStateSwim();
        case Motion::Run: return view.drawStateRun();
        case Motion::Float: return view.drawStateFloat();
        case Motion::Dive: return view.drawStateDive();
        case Motion::Door: return view.drawStateDoor();
        default:
            break;
        }
    }
}