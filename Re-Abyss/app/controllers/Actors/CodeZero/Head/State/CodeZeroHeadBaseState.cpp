#include "CodeZeroHeadBaseState.hpp"
#include <abyss/views/Actors/CodeZero/Head/CodeZeroHeadVM.hpp>
#include <abyss/commons/ActInclude.hpp>

#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss
{
    void CodeZeroHeadBaseState::setup()
    {
        m_hp = *this->binded<HPModel*>();
        m_parent = *this->binded<CodeZeroActor*>();
        m_forward = this->binded<Forward>();
    }
    void CodeZeroHeadBaseState::update([[maybe_unused]]double dt)
    {
        auto playerPos = m_actor->getModule<PlayerActor>()->getPos();
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
    void CodeZeroHeadBaseState::draw() const
    {
        this->m_actor->getBindedView()->draw();
    }
    void CodeZeroHeadBaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const Attacker& attacker) {
            if (m_hp->damage(attacker.getPower()) && m_hp->isDead()) {
                m_parent->onDead();
            }
        });
    }
}
