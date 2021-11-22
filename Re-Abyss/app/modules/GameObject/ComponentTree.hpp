#pragma once

namespace abyss
{
    template <class ... Args>
    struct MultiComponents {};

    template <class T>
    struct ComponentTree
    {
        // using Base = A;
        // or
        // using Base = MultiComponents<A, B, C>;
    };
}