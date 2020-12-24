#pragma once

namespace abyss::Event
{
    class IGlobalTimeScale
    {
    public:
        virtual ~IGlobalTimeScale() = default;

        virtual double getGlobalTimeScale() const = 0;
    };
}