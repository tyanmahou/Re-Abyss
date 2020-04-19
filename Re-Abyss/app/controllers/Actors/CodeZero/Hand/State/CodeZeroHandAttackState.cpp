#include "CodeZeroHandAttackState.hpp"
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss
{
    void CodeZeroHandAttackState::updateRight(double dt)
    {
        const auto& pos = m_body->getPos();
        const auto parentPos = m_parent->getPos();
        if (!m_isReturn && pos.y >= parentPos.y + 250) {
            m_isReturn = true;
            m_body->setVelocityY(-CodeZeroParam::Hand::AttackSpeed);
        } else if (m_isReturn && pos.y <= parentPos.y - 250) {
            m_body->setPosY(parentPos.y - 250);
            this->changeState(State::Pursuit);
        }
        m_body->update(dt);
    }
    void CodeZeroHandAttackState::updateLeft(double dt)
    {
        const auto& pos = m_body->getPos();
        const auto parentPos = m_parent->getPos();
        if (!m_isReturn && pos.x <= parentPos.x - 400) {
            m_isReturn = true;
            m_body->setVelocityX(CodeZeroParam::Hand::AttackSpeed);
        } else if(m_isReturn && pos.x >= parentPos.x + 400){
            m_body->setPosX(parentPos.x + 400);
            this->changeState(State::Pursuit);
        }
        m_body->update(dt);
    }
    CodeZeroHandAttackState::CodeZeroHandAttackState()
    {}
    void CodeZeroHandAttackState::start()
    {
        if (m_actor->isLeftHand()) {
            m_body->setVelocityX(-CodeZeroParam::Hand::AttackSpeed);
        } else {
            m_body->setVelocityY(CodeZeroParam::Hand::AttackSpeed);
        }
    }
}
