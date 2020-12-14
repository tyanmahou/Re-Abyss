#pragma once
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/Decor/base/IDecorAnimationDataStore.hpp>

namespace abyss
{
    class TmxDecorAnimationDataStore : 
        public TmxDataStore,
        public IDecorAnimationDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<DecorAnimationEntity> select()const override;
    };

    using TmxDecorAnimationDataStoreInataller = TmxDataStoreInataller<IDecorAnimationDataStore, TmxDecorAnimationDataStore>;
}