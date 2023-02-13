#pragma once
#include <abyss/datastores/Actor/Land/base/ILandDataStore.hpp>
#include <abyss/datastores/Actor/Land/base/ITileMapDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>

namespace abyss::Actor::Land
{
    class TmxMapDataStore :
        public TmxDataStore,
        public ILandDataStore,
        public ITileMapDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<std::shared_ptr<LandEntity>> select(bool isMerge = true)const override;

       s3d::Vec2 getTileSize() const override;
       s3d::Array<ChunkGrid<LandEntity>> selectGrid() const override;
    };

    struct TmxLandDataStoreInataller final : emaject::IInstaller
    {
        void onBinding(emaject::Container* conatienr) const override
        {
            conatienr->bind<ILandDataStore>()
                .to<TmxMapDataStore>()
                .asCached();
            conatienr->bind<ITileMapDataStore>()
                .to<TmxMapDataStore>()
                .asCached();
        }
    };
}
