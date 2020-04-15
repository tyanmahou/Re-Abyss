#include "TiledDacorDataStore.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
namespace abyss
{
	using namespace s3dTiled;

    TiledDecorDataStore::TiledDecorDataStore(const s3d::String& mapName):
        m_tiledMap(ResourceManager::Main()->loadTmx(mapName + U".tmx"))
    {}
    s3d::Array<DecorEntity> TiledDecorDataStore::select(DecorGroup group) const
    {
        static const std::unordered_map<DecorGroup, s3d::String> toLayerNameMap{
            {DecorGroup::Back, U"back"},
            {DecorGroup::Front, U"front"},
        };
        s3d::Array<DecorEntity> ret;
		auto parser = [&](const ObjectGroup& layer) {
            for (const auto& obj : layer.getObjects()) {
                auto size = obj.toRectF().size;
                auto pos = obj.pos + s3d::Vec2{ size.x / 2, -size.y / 2 };
                DecorEntity entity{
                    .id = obj.id,
                    .group = group,
                    .gId = obj.gId.value_or(0),
                    .pos = pos,
                    .size = size,
                    .rotation = obj.rotation,
                    .isMirrored = obj.isMirrored,
                    .isFliped = obj.isFliped,
                };
                ret.push_back(entity);
            }
		};
        if (auto&& decor = m_tiledMap.getLayer(U"decor")) {
            decor->then([&](const GroupLayer& layer) {
                if (auto l = layer.getLayer(toLayerNameMap.at(group))) {
                    l->then(parser);
                }
            });
        }
        return ret;
    }
}
