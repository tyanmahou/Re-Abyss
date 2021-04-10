#pragma once
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/Decor/base/IAnimationDataStore.hpp>

namespace abyss::decor
{
    class TmxAnimationDataStore :
        public TmxDataStore,
        public IAnimationDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<AnimationEntity> select()const override;
    };

    using TmxAnimationDataStoreInataller = TmxDataStoreInataller<IAnimationDataStore, TmxAnimationDataStore>;
}
