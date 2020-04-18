#include "TmxMapDataStore.hpp"
#include "parser/TmxMapParser.hpp"

namespace abyss
{
	using namespace s3d;
	using namespace s3dTiled;

    s3d::Array<std::shared_ptr<MapEntity>> abyss::TmxMapDataStore::select(bool useAroundFilter) const
    {
		s3d::Array<std::shared_ptr<MapEntity>> ret;
		// 床情報
		auto layer = m_tmx.getLayer(U"map");
		if (!layer) {
			return ret;
		}
		auto parse = [&](const TileLayer& layer) {
			TmxMapParser parser(m_tmx, layer.getGrid(), useAroundFilter);
			parser.forEach([&](const MapEntity& info) {
				ret.push_back(std::make_shared<MapEntity>(info));
			});
		};
		layer->then(parse);
		return ret;
    }

}
