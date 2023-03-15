#include <abyss/scenes/Sequence/Stage/StageSequence.hpp>
#include <abyss/commons/Path.hpp>

namespace
{
    using namespace abyss;
    StageSeqContext ContextDefault()
    {
        return {
            .mapPath = Path::MapPath + U"Stage0/Stage0_0.tmx"
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
        m_pManager->data()->context = Scene::Stage::Context{
            .mapPath = m_context.mapPath
        };
        auto result = co_await m_pManager->changeScene<Scene::Stage::SceneResult>(SceneKind::Stage, 1000);
        // クリアならステージリザルトへ
        if (result.isClear) {
            m_pManager->data()->context = Scene::StageResult::Context{};
            co_await m_pManager->changeScene<void>(SceneKind::StageResult);
        }

        co_return;
    }
}
