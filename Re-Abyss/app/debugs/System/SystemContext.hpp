#pragma once

namespace abyss
{
    class SequenceManager;
}
namespace abyss::Debug
{
    struct SystemContext
    {
        SequenceManager* pSequence = nullptr;
    };
}
