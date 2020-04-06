#pragma once
#include <abyss/commons/Params.hpp>

namespace abyss
{
    template<class Entity>
    struct ParamsGetter
    {
    public: 
        static const Entity* Get()
        {
            return Params::Get<Entity>();
        }
    };
}