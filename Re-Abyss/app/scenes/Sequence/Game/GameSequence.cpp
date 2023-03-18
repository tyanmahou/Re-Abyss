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
        while (true) {
            if (next == SceneKind::Splash) {
                co_await m_pManager->changeScene<void>(SceneKind::Splash);
                next = SceneKind::Title;
            } else if (next == SceneKind::Title) {
                auto result = co_await m_pManager->changeScene<Title::SceneResult>(SceneKind::Title);
                if (result.isStart) {
                    next = SceneKind::SaveSelect;
                    continue;
                } else {
                    m_pManager->exit();
                    co_return;
                }
            } else if (next == SceneKind::SaveSelect) {
                auto result = co_await m_pManager->changeScene<SaveSelect::SceneResult>(SceneKind::SaveSelect);
                if (result.isBack) {
                    next = SceneKind::Title;
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
