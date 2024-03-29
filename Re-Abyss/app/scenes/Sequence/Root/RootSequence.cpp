#include <abyss/scenes/Sequence/Root/RootSequence.hpp>
#include <abyss/scenes/Sequence/Develop/DevelopSequence.hpp>
#include <abyss/scenes/Sequence/Game/GameSequence.hpp>
namespace abyss
{
    using namespace abyss::Scene;

    RootSequence::RootSequence(SequenceManager* pManager) :
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&RootSequence::sequence, this));
    }
    bool RootSequence::onNext()
    {
        return m_seq.resume();
    }
    Coro::Fiber<> RootSequence::sequence()
    {
        co_await m_pManager->changeScene<void>(SceneKind::Boot);

#if ABYSS_DEVELOP
        m_pManager->pushSequence<DevelopSequence>(m_pManager);
        co_yield{};
#endif
        m_pManager->pushSequence<GameSequence>(m_pManager);
        co_yield{};
    }
}
