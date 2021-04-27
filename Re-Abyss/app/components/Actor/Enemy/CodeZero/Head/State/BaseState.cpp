#include "BaseState.hpp"
#include <abyss/components/Actor/utils/ActorUtils.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    void BaseState::setup()
    {
        m_parent = m_pActor->find<ParentCtrl>().get();
        m_head = m_pActor->find<HeadCtrl>().get();

        m_view = m_pActor->find<ViewCtrl<HeadVM>>().get();
    }
    void BaseState::update()
    {
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);
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
