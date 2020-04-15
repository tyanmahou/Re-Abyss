#include "TiledBackGroundDataStore.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/entities/BackGround/BackGroundEntity.hpp>

namespace abyss
{
	using namespace s3dTiled;

    TiledBackGroundDataStore::TiledBackGroundDataStore(const s3d::String& mapName):
        m_tiledMap(ResourceManager::Main()->loadTmx(mapName + U".tmx"))
    {}
    s3d::Array<BackGroundEntity> TiledBackGroundDataStore::select() const
    {
        s3d::Array<BackGroundEntity> ret;
		auto parser = [&](const GroupLayer& layer) {
			for (const auto& child : layer.getLayers()) {
				child.then([&](const ImageLayer& i) {
					BackGroundEntity entity{
						.id = i.getId(),
						.name = i.getName(),
						.filePath = i.getImagePath(),
						.offset = i.getOffset(),
						.loop = { i.getProperty(U"loopX").value_or(false),i.getProperty(U"loopY").value_or(false) },
						.rate = { i.getProperty(U"rateX").value_or(1.0), i.getProperty(U"rateY").value_or(1.0) }
					};
					ret.push_back(std::move(entity));
				});
			}
		};
		m_tiledMap.getLayer(U"bgs")->then(parser);
        return ret;
    }
}
