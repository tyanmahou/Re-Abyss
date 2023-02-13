#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss
{
    TmxDataStore::TmxDataStore(const std::shared_ptr<s3dTiled::TiledMap>& mapData):
        m_tmx(*mapData)
    {}
    TmxDataStore::TmxDataStore(const s3d::String& mapPath) :
        m_tmx(Resource::Assets::Main()->load(mapPath, U""))
    {}

    TiledMapInstaller::TiledMapInstaller(const s3d::String& mapPath):
        m_tmx(std::make_shared<s3dTiled::TiledMap>(Resource::Assets::Main()->load(mapPath, U"")))
    {}

    void TiledMapInstaller::onBinding(emaject::Container * conatienr) const
    {
        conatienr->bind<s3dTiled::TiledMap>()
            .fromInstance(m_tmx)
            .asCached();
    }

}
