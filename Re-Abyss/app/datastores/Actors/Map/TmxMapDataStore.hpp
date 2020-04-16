#pragma once
#include <abyss/datastores/Actors/Map/base/IMapDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>

namespace abyss
{
    class TmxMapDataStore :
        public TmxDataStore,
        public IMapDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<std::shared_ptr<MapEntity>> select(bool useAroundFilter = true)const override;
    };
}