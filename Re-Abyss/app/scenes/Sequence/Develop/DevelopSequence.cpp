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
            m_pManager->changeScene(SceneKind::DevPortal);
            co_yield{};
            if (m_pManager->getResult<Scene::DevPortal::SceneResult>().command == Scene::DevPortal::SceneResult::GameStart) {
                break;
            }
            m_pManager->changeScene(SceneKind::Experiment);
            co_yield{};
        }
    }
}
#endif
