#include "WaitState.hpp"
#include "PursuitState.hpp"
#include <abyss/controllers/System/System.hpp>
namespace abyss::Ikalien
{
    void WaitState::start()
    {
        m_draw->request(DrawModel::Kind::Wait);
    }
    void WaitState::update([[maybe_unused]]double dt)
    {
        if (m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<PursuitState>();
        }
    }
}
