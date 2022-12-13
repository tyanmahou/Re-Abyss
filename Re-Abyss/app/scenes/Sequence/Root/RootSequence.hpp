#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss
{
    class RootSequence : public ISequence
    {
    public:
        RootSequence(SequenceManager* pManager);

        bool onNext() override;
    private:
        Coro::Fiber<> sequence();
    private:
        SequenceManager* m_pManager;
        Coro::FiberHolder<> m_seq;
    };
}
