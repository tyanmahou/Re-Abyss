#pragma once
#include <abyss/scenes/SequenceManager.hpp>

namespace abyss
{
    class MainSequence : public ISequence
    {
    public:
        MainSequence(SequenceManager* pManager);

    private:
        SequenceManager* m_pManager;
    };
}
