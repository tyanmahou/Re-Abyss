#pragma once
#include<memory>

#include<Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    class IMapCollisionModel
    {
    public:
        virtual ~IMapCollisionModel() = default;

        virtual void collisionAll(
            const s3d::Array<Ref<Actor::IPhysics>>& physics, 
            const s3d::Array<Ref<Actor::Terrain>>& terrains
        ) = 0;
        
    };

    class SimpleMapCollision : public IMapCollisionModel
    {
    public:
        void collisionAll(
            const s3d::Array<Ref<Actor::IPhysics>>& physics,
            const s3d::Array<Ref<Actor::Terrain>>& terrains
        )override;
    };
}