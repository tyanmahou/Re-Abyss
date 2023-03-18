#include <abyss/scenes/Sequence/Stage/StageSequence.hpp>
#include <abyss/commons/Path.hpp>

namespace
{
    using namespace abyss;
    StageSeqContext ContextDefault()
    {
        return {
            .stage = StageDef::Stage0()
        };
    }
}
namespace abyss
{
    StageSequence::StageSequence(SequenceManager* pManager):
        StageSequence(pManager, ::ContextDefault())
    {
    }
    StageSequence::StageSequence(SequenceManager* pManager, const StageSeqContext& context):
        m_pManager(pManager),
        m_context(context)
    {
        m_seq.reset(std::bind(&StageSequence::sequence, this));
    }
    bool StageSequence::onNext()
    {
        return m_seq.resume();
    }
    Coro::Fiber<> StageSequence::sequence()
    {
        // ステージイン
        auto result = co_await m_pManager->changeScene<Scene::Stage::Context, Scene::Stage::SceneResult>(SceneKind::Stage, {
            .stage = m_context.stage
        });
        // クリアならステージリザルトへ
        if (result.isClear) {
            co_await m_pManager->changeScene<Scene::StageResult::Context, void>(SceneKind::StageResult, {
                .stage = m_context.stage
            });
        }

        co_return;
    }
}
