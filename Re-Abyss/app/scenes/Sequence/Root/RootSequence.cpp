#include <abyss/scenes/Sequence/Root/RootSequence.hpp>
#include <abyss/scenes/Sequence/User/UserSequence.hpp>

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
        return m_seq.moveNext();
    }
    Coro::Task<> RootSequence::sequence()
    {
        m_pManager->changeScene(SceneKind::Root);
        co_yield{};
        m_pManager->changeScene(SceneKind::Splash);
        co_yield{};

        SceneKind next = SceneKind::Title;
        s3d::int32 transitionMsec = 0;
        while (true) {
            if (next == SceneKind::Title) {
                m_pManager->changeScene(SceneKind::Title, transitionMsec);
                co_yield{};
                if (m_pManager->getResult<Title::SceneResult>().isStart) {
                    next = SceneKind::SaveSelect;
                    transitionMsec = 1000;
                    continue;
                } else {
                    co_return;
                }
            } else if (next == SceneKind::SaveSelect) {
                m_pManager->changeScene(SceneKind::SaveSelect, transitionMsec);
                co_yield{};
                auto result = m_pManager->getResult<SaveSelect::SceneResult>();
                if (result.isBack) {
                    next = SceneKind::Title;
                    transitionMsec = 1000;
                    continue;
                } else {
                    m_pManager->pushSequence<UserSequence>(m_pManager);
                    co_yield{};
                    next = SceneKind::Title;
                    continue;
                }
            } else {
                break;
            }
        }
        co_return;
    }
}
