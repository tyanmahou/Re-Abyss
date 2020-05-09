#pragma once
#include <tuple>
namespace abyss
{
    class IComponent
    {
    public:
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual void setup() {}
    };

    template<class T>
    struct ComponentTree
    {
        // using Base = A;
        // or
        // using Base = std::tuple<A, B, C>;
    };
}