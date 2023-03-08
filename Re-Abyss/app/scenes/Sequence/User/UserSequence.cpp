#include <abyss/scenes/Sequence/User/UserSequence.hpp>
#include <abyss/scenes/Sequence/Stage/StageSequence.hpp>

namespace abyss
{
    UserSequence::UserSequence(SequenceManager* pManager):
        m_pManager(pManager)
    {
        m_seq.reset(std::bind(&UserSequence::sequence, this));
    }
    bool UserSequence::onNext()
    {
        return m_seq.resume();
    }
    Coro::Fiber<> UserSequence::sequence()
    {
        m_pManager->changeScene(SceneKind::Home);
        co_yield{};

        m_pManager->pushSequence<StageSequence>(m_pManager);
        co_yield{};

        co_return;
    }
}
