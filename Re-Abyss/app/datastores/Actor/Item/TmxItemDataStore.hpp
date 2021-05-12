#pragma once
#include <abyss/datastores/Actor/Item/base/IItemDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>

namespace abyss::Actor::Item
{
    class TmxItemDataStore:
        public TmxDataStore,
        public IItemDataStore
    { 
    public:
        using TmxDataStore::TmxDataStore;
        s3d::Array<std::shared_ptr<ItemEntity>> select()const override;
    };


    using TmxItemDataStoreInataller = TmxDataStoreInataller<IItemDataStore, TmxItemDataStore>;
}