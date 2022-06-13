#include <abyss/datastores/Actor/Land/TmxLandDataStore.hpp>
#include <abyss/datastores/Actor/Land/parser/TmxLandParser.hpp>
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

namespace abyss::Actor::Land
{
	using namespace s3d;
	using namespace s3dTiled;

    s3d::Array<std::shared_ptr<LandEntity>> TmxMapDataStore::select(bool isMerge) const
    {
		s3d::Array<std::shared_ptr<LandEntity>> ret;
		// 床情報
		auto layer = m_tmx.getLayer(U"land");
		if (!layer) {
			return ret;
		}

		TmxParseUtil::ParseForGroup(*layer, [&](const TileLayer& layer) {
			TmxLandParser parser(m_tmx, layer.getChunk(), isMerge);
			parser.forEach([&](const LandEntity& info) {
				ret.push_back(std::make_shared<LandEntity>(info));
			});
		});

		return ret;
    }

	s3d::Vec2 TmxMapDataStore::getTileSize() const
	{
		return s3d::Vec2(m_tmx.getTileSize());
	}

	s3d::Array<ChunkGrid<LandEntity>> TmxMapDataStore::selectGrid() const
	{
		s3d::Array<ChunkGrid<LandEntity>> ret;
		auto layer = m_tmx.getLayer(U"land");
		if (!layer) {
			return ret;
		}
		TmxParseUtil::ParseForGroup(*layer, [&](const TileLayer& layer) {
			TmxLandParser parser(m_tmx, layer.getChunk());
			ChunkGrid<LandEntity> a;

			const auto& chunk = parser.selectGrid();
			for (int32 y = chunk.indexBegin(); y < chunk.indexEnd(); ++y) {
				const auto& row = chunk[y];
				for (int32 x = row.indexBegin(); x < row.indexEnd(); ++x) {
					if (auto&& elm = chunk[y][x]; elm) {
						a[y][x] = *elm;
					}
				}
			}
			ret.push_back(std::move(a));
		});

		return ret;
	}

}
