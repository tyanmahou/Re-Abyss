#pragma once

namespace abyss
{
    class IComponent
    {
    public:
        virtual ~IComponent() = default;

        virtual void setup() = 0;
    };
}