#include "TmxDataStore.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss
{
    TmxDataStore::TmxDataStore(const s3d::String& mapName) :
        m_tmx(Resource::Assets::Main()->loadTmx(mapName + U".tmx"))
    {}

}
