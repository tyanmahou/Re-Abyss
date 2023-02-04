#pragma once
#if ABYSS_DEVELOP
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss
{
    class DevelopSequence : public ISequence
    {
    public:
        DevelopSequence(SequenceManager* pManager);
        bool onNext() override;
    private:
        Coro::Fiber<> sequence();
    private:
        SequenceManager* m_pManager;
        Coro::FiberHolder<> m_seq;
    };
}
#endif
