#pragma once
namespace abyss
{
    class IComponent
    {
    public:
        IComponent() = default;
        virtual ~IComponent() = default;

        virtual void setup() {}

        virtual void onStart() {};
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