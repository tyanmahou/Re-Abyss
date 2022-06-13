#include <abyss/scenes/Sequence/Stage/StageSequence.hpp>

namespace abyss
{
    StageSequence::StageSequence(SequenceManager* pManager):
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&StageSequence::sequence, this));
    }
    bool StageSequence::onNext()
    {
        return m_seq.moveNext();
    }
    Coro::Task<> StageSequence::sequence()
    {
        m_pManager->changeScene(SceneKind::Stage);
        co_yield{};

        m_pManager->changeScene(SceneKind::StageResult);
        co_yield{};

        co_return;
    }
}
