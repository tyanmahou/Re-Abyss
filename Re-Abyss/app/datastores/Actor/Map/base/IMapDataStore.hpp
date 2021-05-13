#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/entities/Actor/Map/MapEntity.hpp>

namespace abyss::Actor::Map
{
    class IMapDataStore
    {
    public:
        virtual ~IMapDataStore() = default;

        s3d::Array<std::shared_ptr<MapEntity>> selectFiltered() const
        {
            return this->select(true);
        }
        virtual s3d::Array<std::shared_ptr<MapEntity>> select(bool isMerge = true)const = 0;
    };
}