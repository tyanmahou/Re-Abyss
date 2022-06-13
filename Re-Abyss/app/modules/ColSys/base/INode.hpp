#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/Collision/CShape.hpp>

namespace abyss::ColSys
{
    class INode
    {
    public:
        virtual ~INode() = default;
        virtual CShape getShape() const = 0;
    };
}