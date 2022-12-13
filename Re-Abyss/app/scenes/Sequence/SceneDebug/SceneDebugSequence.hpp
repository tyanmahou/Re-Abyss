#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss
{
    class SceneDebugSequence : public ISequence
    {
    public:
        SceneDebugSequence(SequenceManager* pManager, SceneKind kind);

        bool onNext() override;
    private:
        Coro::Fiber<> sequence(SceneKind kind);
    private:
        SequenceManager* m_pManager;
        Coro::FiberHolder<> m_seq;
    };
}
