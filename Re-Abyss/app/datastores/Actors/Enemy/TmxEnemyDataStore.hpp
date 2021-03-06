#pragma once
#include <abyss/datastores/Actors/Enemy/base/IEnemyDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>

namespace abyss
{
    class TmxEnemyDataStore:
        public TmxDataStore,
        public IEnemyDataStore
    { 
    public:
        using TmxDataStore::TmxDataStore;
        s3d::Array<std::shared_ptr<EnemyEntity>> select()const override;
    };


    using TmxEnemyDataStoreInataller = TmxDataStoreInataller<IEnemyDataStore, TmxEnemyDataStore>;
}