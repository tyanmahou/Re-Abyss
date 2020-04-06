#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/datastores/Params/base/IParamsDataStore.hpp>

namespace abyss
{
    template<class Entity>
    class IParamsRepository
    {
    public:
        virtual ~IParamsRepository() = default;

        virtual const Entity& select() = 0;
    };
}