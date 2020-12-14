#pragma once
#include <S3DTiled.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>

namespace abyss
{
    class TmxDecorDataStore :
        public TmxDataStore,
        public IDecorDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<DecorEntity> select(DecorGroup group)const override;
    };

    using TmxDecorDataStoreInataller = TmxDataStoreInataller<IDecorDataStore, TmxDecorDataStore>;
}