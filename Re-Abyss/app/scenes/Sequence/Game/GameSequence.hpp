#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss
{
    class GameSequence : public ISequence
    {
    public:
        GameSequence(SequenceManager* pManager);
        GameSequence(SequenceManager* pManager, SceneKind initScene);
        bool onNext() override;
    private:
        Coro::Task<> sequence(SceneKind initScene);
    private:
        SequenceManager* m_pManager;
        Coro::TaskHolder<> m_seq;
    };
}