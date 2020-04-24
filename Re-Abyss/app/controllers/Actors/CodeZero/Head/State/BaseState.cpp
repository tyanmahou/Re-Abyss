#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Head/HeadVM.hpp>
#include <abyss/commons/ActInclude.hpp>

#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss::CodeZero::Head
{
    void BaseState::setup()
    {
        m_hp = *this->binded<HPModel*>();
        m_parent = *this->binded<CodeZeroActor*>();
        m_forward = this->binded<Forward>();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
        auto playerPos = m_actor->getModule<Player::PlayerActor>()->getPos();
        auto pos = m_actor->getPos();

        if (m_parent->isShotCharge()) {
            *m_forward = Forward::None;
        }else if (playerPos.x > pos.x + 200) {
            *m_forward = Forward::Right;
        } else if (playerPos.x < pos.x - 200) {
            *m_forward = Forward::Left;
        } else {
            *m_forward = Forward::None;
        }
    }
    void BaseState::draw() const
    {
        this->m_actor->getBindedView()->draw();
    }
    void BaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const Attacker& attacker) {
            if (m_hp->damage(attacker.getPower()) && m_hp->isDead()) {
                m_parent->onDead();
            }
        });
    }
}
