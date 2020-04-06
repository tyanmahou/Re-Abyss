#pragma once

namespace abyss
{
    template<class Entity>
    class IParamsDataStore
    {
    public:
        virtual ~IParamsDataStore() = default;

        virtual Entity select() const = 0;
    };
}