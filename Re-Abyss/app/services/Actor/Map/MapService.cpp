#include <abyss/services/Actor/Map/MapService.hpp>
#include <abyss/datastores/Actor/Map/base/IMapDataStore.hpp>

namespace abyss::Actor::Map
{
    MapService::MapService(std::shared_ptr<IMapDataStore> maps):
        m_maps(maps->select())
    {}

    const s3d::Array<std::shared_ptr<MapEntity>>& MapService::getMaps() const
    {
        return m_maps;
    }

    void MapServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IMapService>()
            .to<MapService>()
            .asCache();
    }
}
