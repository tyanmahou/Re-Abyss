#pragma once
#include <abyss/utils/Collision/CShape.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>

namespace abyss::Physics
{
    class IContacter
    {
    public:
        virtual ~IContacter() = default;

        virtual void setId(s3d::uint64 id) = 0;
        virtual s3d::uint64 id() const = 0;

        virtual bool isActive() const = 0;
        virtual bool isDestroyed() const = 0;

        virtual const CShape& getShape() const = 0;
        virtual void onCollision(const TerrainData&) = 0;
    };
}