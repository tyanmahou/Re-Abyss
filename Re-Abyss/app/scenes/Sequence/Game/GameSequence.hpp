#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss
{
    class GameSequence : public ISequence
    {
    public:
        GameSequence(SequenceManager* pManager);
        GameSequence(SequenceManager* pManager, SceneKind initScene);
        bool onNext() override;
    private:
        Coro::Fiber<> sequence(SceneKind initScene);
    private:
        SequenceManager* m_pManager;
        Coro::FiberHolder<> m_seq;
    };
}
