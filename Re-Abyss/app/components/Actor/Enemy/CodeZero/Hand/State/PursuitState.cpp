#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/PursuitState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    void PursuitState::start()
    {
        if (m_desc) {
            m_handMove->setParam(*m_desc);
        }
        m_handMove->startForPursuit(m_slowStart);
    }

    PursuitState::PursuitState(const s3d::Optional<HandDesc>& desc, bool slowStart):
        m_desc(desc),
        m_slowStart(slowStart)
    {}

    void PursuitState::update()
    {
    }

    void PursuitState::lastUpdate()
    {
    }
}
