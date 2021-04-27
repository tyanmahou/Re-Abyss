#pragma once
#include <abyss/datastores/Actor/Map/base/IMapDataStore.hpp>
#include <abyss/datastores/Actor/Map/base/ITileMapDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>

namespace abyss
{
    class TmxMapDataStore :
        public TmxDataStore,
        public IMapDataStore,
        public ITileMapDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<std::shared_ptr<MapEntity>> select(bool isMerge = true)const override;

       s3d::Vec2 getTileSize() const override;
        s3d::Grid<s3d::uint32> selectRawGrid() const override;
    };

    struct TmxMapDataStoreInataller final : emaject::IInstaller
    {
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<IMapDataStore>()
                .to<TmxMapDataStore>()
                .asCache();
            conatienr->bind<ITileMapDataStore>()
                .to<TmxMapDataStore>()
                .asCache();
        }
    };
}