#include "BaseState.hpp"
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>

namespace abyss::Actor::CodeZero::Head
{
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrlModel>().get();
        m_head = m_pActor->find<HeadModel>().get();

        m_view = m_pActor->find<ViewModel<HeadVM>>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
        auto playerPos = m_pActor->getModule<Player::PlayerActor>()->getPos();
        auto pos = m_head->getPos();

        if (m_parent->isShotCharge()) {
            m_head->setForward(Forward::None);
        }else if (playerPos.x > pos.x + 200) {
            m_head->setForward(Forward::Right);
        } else if (playerPos.x < pos.x - 200) {
            m_head->setForward(Forward::Left);
        } else {
            m_head->setForward(Forward::None);
        }
    }
    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
