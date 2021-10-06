#pragma once
#include <abyss/components/base/Executer.hpp>
#include <abyss/components/base/ComponentTree.hpp>

namespace abyss
{
    class IComponent
    {
    public:
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual void setup([[maybe_unused]]Executer executer) {}

        virtual void onStart() {}
        virtual void onEnd() {}
    };
}