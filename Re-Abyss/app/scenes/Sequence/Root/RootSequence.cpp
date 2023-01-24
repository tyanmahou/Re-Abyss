#include <abyss/scenes/Sequence/Root/RootSequence.hpp>
#include <abyss/scenes/Sequence/Develop/DevlopSequence.hpp>
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
        m_pManager->changeScene(SceneKind::Boot);
        co_yield{};

#if ABYSS_DEVELOP
        m_pManager->pushSequence<DevelopSequence>(m_pManager);
        co_yield{};
#endif
        m_pManager->pushSequence<GameSequence>(m_pManager);
        co_yield{};
    }
}
