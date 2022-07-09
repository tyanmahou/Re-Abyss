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
        return m_seq.moveNext();
    }
    Coro::Task<> StageSequence::sequence()
    {
        // ステージイン
        {
            m_pManager->data()->context = Scene::Stage::Context{
                .mapPath = m_context.mapPath
            };
            m_pManager->changeScene(SceneKind::Stage, 1000);
        }
        co_yield{};

        // クリアならステージリザルトへ
        if (auto result = m_pManager->getResult<Scene::Stage::SceneResult>(); result.isClear) {
            m_pManager->data()->context = Scene::StageResult::Context{};
            m_pManager->changeScene(SceneKind::StageResult);
            co_yield{};
        }

        co_return;
    }
}
