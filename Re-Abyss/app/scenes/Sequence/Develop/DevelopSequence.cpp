#include <abyss/scenes/Sequence/Develop/DevelopSequence.hpp>
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
        while (true)
        {
            auto result = co_await m_pManager->changeScene<Scene::DevPortal::SceneResult>(SceneKind::DevPortal);
            if (result.command == Scene::DevPortal::SceneResult::GameStart) {
                break;
            }
            co_await m_pManager->changeScene<void>(SceneKind::Experiment);
        }
    }
}
#endif
