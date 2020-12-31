#pragma once
#include <abyss/components/base/Executer.hpp>

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

    template <class ... Args>
    struct MultiComponents{};

    template <class T>
    struct ComponentTree
    {
        // using Base = A;
        // or
        // using Base = MultiComponents<A, B, C>;
    };
}