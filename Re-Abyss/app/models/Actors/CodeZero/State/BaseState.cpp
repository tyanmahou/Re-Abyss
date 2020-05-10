#include "BaseState.hpp"
#include <abyss/views/Actors/CodeZero/Body/BodyVM.hpp>
#include <Siv3D.hpp>

namespace abyss::CodeZero
{
    BaseState::BaseState()
    {}
    void BaseState::setup()
    {
        m_hp = m_pActor->find<HPModel>().get();
        m_pattern = m_pActor->find<PatternModel>().get();
    }
    void BaseState::update([[maybe_unused]]double dt)
    {
    }
    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }
}
