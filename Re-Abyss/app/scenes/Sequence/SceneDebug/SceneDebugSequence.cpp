#include <abyss/scenes/Sequence/SceneDebug/SceneDebugSequence.hpp>
#if ABYSS_DEBUG
namespace abyss
{
    using namespace abyss::Scene;

    SceneDebugSequence::SceneDebugSequence(SequenceManager* pManager, SceneKind kind):
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&SceneDebugSequence::sequence, this, kind));
    }
    bool SceneDebugSequence::onNext()
    {
        return m_seq.resume();
    }
    Coro::Fiber<> SceneDebugSequence::sequence(SceneKind kind)
    {
        m_pManager->changeScene(kind, 1000);
        co_yield{};
    }
}
#endif
