#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss::Cycle
{
    class CycleObj final : private GameObject
    {
    public:
        using GameObject::setManager;
        using GameObject::setup;
        using GameObject::start;
        using GameObject::end;
        using GameObject::attach;
        using GameObject::find;

        bool listen();
    };
}