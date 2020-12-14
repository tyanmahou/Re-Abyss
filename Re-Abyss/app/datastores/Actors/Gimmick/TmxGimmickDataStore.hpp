#pragma once
#include <abyss/datastores/Actors/Gimmick/base/IGimmickDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>

namespace abyss
{
    class TmxGimmickDataStore :
        public TmxDataStore,
        public IGimmickDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;
        s3d::Array<std::shared_ptr<GimmickEntity>> select()const override;
    };

    using TmxGimmickDataStoreInataller = TmxDataStoreInataller<IGimmickDataStore, TmxGimmickDataStore>;
}