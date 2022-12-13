#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Fiber/FiberHolder.hpp>

namespace abyss
{
    class UserSequence : public ISequence
    {
    public:
        UserSequence(SequenceManager* pManager);

        bool onNext() override;
    private:
        Coro::Fiber<> sequence();
    private:
        SequenceManager* m_pManager;
        Coro::FiberHolder<> m_seq;
    };
}
