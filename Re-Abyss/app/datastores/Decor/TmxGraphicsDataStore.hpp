#pragma once
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/Decor/base/IGraphicsDataStore.hpp>

namespace abyss::Decor
{
    class TmxGraphicsDataStore :
        public TmxDataStore,
        public IGraphicsDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<GraphicsEntity> select()const override;
    };

    using TmxGraphicsDataStoreInataller = TmxDataStoreInataller<IGraphicsDataStore, TmxGraphicsDataStore>;
}
