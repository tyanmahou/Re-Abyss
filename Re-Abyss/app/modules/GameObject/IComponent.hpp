#pragma once
#include <abyss/modules/GameObject/Executer.hpp>
#include <abyss/modules/GameObject/ComponentTree.hpp>

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