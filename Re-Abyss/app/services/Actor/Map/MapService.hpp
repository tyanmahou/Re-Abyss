#pragma once
#include <abyss/services/Actor/Map/base/IMapService.hpp>
#include <Emaject.hpp>

namespace abyss::Actor::Map
{
    class IMapDataStore;

    class MapService : public IMapService
    {
    public:
        INJECT_CTOR(MapService(
            std::shared_ptr<IMapDataStore> maps
        ));
        const s3d::Array<std::shared_ptr<MapEntity>>& getMaps() const override;
    private:
        s3d::Array<std::shared_ptr<MapEntity>> m_maps;
    };

    struct MapServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}