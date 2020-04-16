#include "TmxDataStore.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss
{
    TmxDataStore::TmxDataStore(const s3d::String& mapName) :
        m_tmx(ResourceManager::Main()->loadTmx(mapName + U".tmx"))
    {}

}
