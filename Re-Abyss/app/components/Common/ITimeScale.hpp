#pragma once

namespace abyss
{
    class ITimeScale
    {
    public:
        virtual ~ITimeScale() = default;

        virtual double timeScale() = 0;
    };
}