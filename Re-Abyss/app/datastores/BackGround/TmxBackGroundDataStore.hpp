#pragma once
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/BackGround/base/IBackGroundDataStore.hpp>

namespace abyss
{
    class TmxBackGroundDataStore : 
        public TmxDataStore,
        public IBackGroundDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<BackGroundEntity> select()const override;
    };
}