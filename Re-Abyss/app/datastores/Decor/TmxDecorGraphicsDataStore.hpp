#pragma once
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/Decor/base/IDecorGraphicsDataStore.hpp>

namespace abyss
{
    class TmxDecorGraphicsDataStore :
        public TmxDataStore,
        public IDecorGraphicsDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<DecorGraphicsEntity> select()const override;
    };

    using TmxDecorGraphicsDataStoreInataller = TmxDataStoreInataller<IDecorGraphicsDataStore, TmxDecorGraphicsDataStore>;
}