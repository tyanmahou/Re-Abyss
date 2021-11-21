#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Collision
{
    class INode
    {
    public:
        virtual ~INode() = default;
        virtual const CShape& getShape() const = 0;
    };
}