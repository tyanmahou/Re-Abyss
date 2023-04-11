#include <abyss/scenes/Sequence/User/UserSequence.hpp>
#include <abyss/scenes/Sequence/Stage/StageSequence.hpp>

namespace abyss
{
    using namespace abyss::Scene;

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
        while (true)
        {
            auto result = co_await m_pManager->changeScene<Home::SceneResult>(SceneKind::Home);
            if (result.isBack) {
                co_return;
            } else {
                m_pManager->pushSequence<StageSequence>(m_pManager, StageSeqContext{
                    .stage = result.stage
                });
                co_yield{};
            }
        }
        co_return;
    }
}
