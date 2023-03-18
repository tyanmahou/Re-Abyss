#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>
#include <abyss/values/StageDef.hpp>

namespace abyss
{
    struct StageSeqContext
    {
        StageDef stage;
    };

    class StageSequence : public ISequence
    {
    public:
        StageSequence(SequenceManager* pManager);
        StageSequence(SequenceManager* pManager, const StageSeqContext& context);

        bool onNext() override;
    private:
        Coro::Fiber<> sequence();
    private:
        SequenceManager* m_pManager;
        StageSeqContext m_context;
        Coro::FiberHolder<> m_seq;
    };
}
