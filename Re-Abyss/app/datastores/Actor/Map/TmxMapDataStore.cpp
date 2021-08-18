#include "TmxMapDataStore.hpp"
#include "parser/TmxMapParser.hpp"
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

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

		TmxParseUtil::ParseForGroup(*layer, [&](const TileLayer& layer) {
			TmxMapParser parser(m_tmx, layer.getChunk(), isMerge);
			parser.forEach([&](const MapEntity& info) {
				ret.push_back(std::make_shared<MapEntity>(info));
			});
		});

		return ret;
    }

	s3d::Vec2 TmxMapDataStore::getTileSize() const
	{
		return s3d::Vec2(m_tmx.getTileSize());
	}

	s3d::Array<ChunkGrid<s3d::uint32>> TmxMapDataStore::selectRawGrid() const
	{
		s3d::Array<ChunkGrid<s3d::uint32>> ret;
		auto layer = m_tmx.getLayer(U"map");
		if (!layer) {
			return ret;
		}
		TmxParseUtil::ParseForGroup(*layer, [&](const TileLayer& layer) {
			ChunkGrid<s3d::uint32> a;

			const auto& chunk = layer.getChunk();
			const auto& chunkSize = chunk.chunkSize();

			for (auto&& [xBase, column] : chunk) {
				for (auto&& [yBase, grid] : column) {
					for (int32 y = 0; y < grid.height(); ++y) {
						for (int32 x = 0; x < grid.width(); ++x) {
							a[yBase * chunkSize.y + y][xBase * chunkSize.x + x] = grid[y][x];
						}
					}
				}
			}
			ret.push_back(std::move(a));
		});

		return ret;
	}

}
