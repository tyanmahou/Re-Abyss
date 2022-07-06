#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss
{
    class SceneDebugSequence : public ISequence
    {
    public:
        SceneDebugSequence(SequenceManager* pManager, SceneKind kind);

        bool onNext() override;
    private:
        Coro::Task<> sequence(SceneKind kind);
    private:
        SequenceManager* m_pManager;
        Coro::TaskHolder<> m_seq;
    };
}
