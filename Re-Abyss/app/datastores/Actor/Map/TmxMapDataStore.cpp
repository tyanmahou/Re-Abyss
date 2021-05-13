#include "TmxMapDataStore.hpp"
#include "parser/TmxMapParser.hpp"

namespace abyss::Actor::Map
{
	using namespace s3d;
	using namespace s3dTiled;

    s3d::Array<std::shared_ptr<MapEntity>> TmxMapDataStore::select(bool isMerge) const
    {
		s3d::Array<std::shared_ptr<MapEntity>> ret;
		// 床情報
		auto layer = m_tmx.getLayer(U"map");
		if (!layer) {
			return ret;
		}
		auto parse = [&](const TileLayer& layer) {
			TmxMapParser parser(m_tmx, layer.getGrid(), isMerge);
			parser.forEach([&](const MapEntity& info) {
				ret.push_back(std::make_shared<MapEntity>(info));
			});
		};
		layer->then(parse);
		return ret;
    }

	s3d::Vec2 TmxMapDataStore::getTileSize() const
	{
		return s3d::Vec2(m_tmx.getTileSize());
	}

	s3d::Grid<s3d::uint32> TmxMapDataStore::selectRawGrid() const
	{
		s3d::Grid<s3d::uint32> ret;
		auto layer = m_tmx.getLayer(U"map");
		if (!layer) {
			return ret;
		}
		layer->then([&](const TileLayer& layer) {
			ret = layer.getGrid();
		});
		return ret;
	}

}
