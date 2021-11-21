#pragma once
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Collision
{
    class INode
    {
    public:
        virtual ~INode() = default;

        virtual s3d::uint64 id() const = 0;
        virtual s3d::uint32 layer() const = 0;
        virtual s3d::uint32 toLayer() const = 0;

        virtual bool isActive() const = 0;
        virtual bool isDestroyed() const = 0;

        virtual const CShape& getShape() const = 0;
        virtual void onCollision(const Ref<INode>&) = 0;
    };
}