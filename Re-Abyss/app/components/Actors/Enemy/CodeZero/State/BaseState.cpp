#include "BaseState.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    BaseState::BaseState()
    {}
    void BaseState::setup()
    {
        m_hp = m_pActor->find<HPModel>().get();
        m_pattern = m_pActor->find<PatternCtrl>().get();
        m_parts = m_pActor->find<PartsCtrl>().get();
        m_view = m_pActor->find<ViewModel<Body::BodyVM>>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
