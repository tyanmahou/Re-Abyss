#pragma once
#include <abyss/scenes/SequenceManager.hpp>
#include <abyss/utils/Coro/Task/TaskHolder.hpp>

namespace abyss
{
    class RootSequence : public ISequence
    {
    public:
        RootSequence(SequenceManager* pManager);

        bool onNext() override;
    private:
        Coro::Task<> sequence();
    private:
        SequenceManager* m_pManager;
        Coro::TaskHolder<> m_seq;
    };
}
