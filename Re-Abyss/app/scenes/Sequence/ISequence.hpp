#pragma once

namespace abyss
{
    class ISequence
    {
    public:
        virtual ~ISequence() = default;
        virtual bool onNext() = 0;
    };
}
