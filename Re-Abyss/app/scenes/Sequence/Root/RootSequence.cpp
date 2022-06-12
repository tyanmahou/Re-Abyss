#include <abyss/scenes/Sequence/Root/RootSequence.hpp>

namespace abyss
{
    RootSequence::RootSequence(SequenceManager* pManager) :
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&RootSequence::sequence, this));
    }
    bool RootSequence::onNext()
    {
        return m_seq.moveNext();
    }
    Coro::Task<> RootSequence::sequence()
    {
        m_pManager->changeScene(SceneKind::Root);
        co_yield{};
        m_pManager->changeScene(SceneKind::Splash);
        co_yield{};
        while (true) {
            m_pManager->changeScene(SceneKind::Title);
            co_yield{};
            if (m_pManager->getResult<Title::SceneResult>().isStart) {
                m_pManager->changeScene(SceneKind::SaveSelect, 1000);
                co_yield{};
            } else {
                co_return;
            }
        }
        co_return;
    }
}
