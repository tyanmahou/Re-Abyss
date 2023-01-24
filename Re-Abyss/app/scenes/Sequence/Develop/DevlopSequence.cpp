#include <abyss/scenes/Sequence/Develop/DevlopSequence.hpp>
#if ABYSS_DEVELOP

namespace abyss
{
    DevelopSequence::DevelopSequence(SequenceManager* pManager):
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&DevelopSequence::sequence, this));
    }
    bool DevelopSequence::onNext()
    {
        return m_seq.resume();
    }
    Coro::Fiber<> DevelopSequence::sequence()
    {
        m_pManager->changeScene(SceneKind::DevPortal);
        co_yield{};
    }
}
#endif
