#include <abyss/components/Actor/Common/BossFadeMask.hpp>

namespace abyss::Actor
{
    BossFadeMask::BossFadeMask(ActorObj* pActor):
        m_pActor(pActor)
    {
    }
    void BossFadeMask::setup(Executer executer)
    {
        if (m_drawer) {
            m_drawer->setup(executer);
        }
    }
    void BossFadeMask::onStart()
    {
        if (m_drawer) {
            m_drawer->onStart();
        }
    }

    void BossFadeMask::onDraw() const
    {
        if (m_drawer) {
            m_drawer->onDraw();
        }
    }
}
