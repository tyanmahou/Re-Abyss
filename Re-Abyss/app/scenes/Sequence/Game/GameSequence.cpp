#include <abyss/scenes/Sequence/Game/GameSequence.hpp>
#include <abyss/scenes/Sequence/User/UserSequence.hpp>

namespace abyss
{
    using namespace abyss::Scene;

    GameSequence::GameSequence(SequenceManager* pManager) :
        GameSequence(pManager, SceneKind::Splash)
    {
    }
    GameSequence::GameSequence(SequenceManager* pManager, SceneKind initScene):
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&GameSequence::sequence, this, initScene));
    }
    bool GameSequence::onNext()
    {
        return m_seq.resume();
    }
    Coro::Fiber<> GameSequence::sequence(const SceneKind initScene)
    {
        SceneKind next = initScene;
        s3d::int32 transitionMsec = 0;
        while (true) {
            if (next == SceneKind::Splash) {
                m_pManager->changeScene(SceneKind::Splash);
                co_yield{};
                next = SceneKind::Title;
            } else if (next == SceneKind::Title) {
                m_pManager->changeScene(SceneKind::Title, transitionMsec);
                co_yield{};
                if (m_pManager->getResult<Title::SceneResult>().isStart) {
                    next = SceneKind::SaveSelect;
                    transitionMsec = 1000;
                    continue;
                } else {
                    m_pManager->exit();
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
                    transitionMsec = 1000;
                    continue;
                }
            } else {
                break;
            }
        }
        co_return;
    }
}
