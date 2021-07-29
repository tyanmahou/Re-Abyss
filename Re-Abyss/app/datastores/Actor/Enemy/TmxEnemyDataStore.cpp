#include "TmxEnemyDataStore.hpp"
#include "parser/TmxEnemyParser.hpp"
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

namespace abyss::Actor::Enemy
{
	using namespace s3d;
	using namespace s3dTiled;

	s3d::Array<std::shared_ptr<EnemyEntity>> TmxEnemyDataStore::select() const
    {
		s3d::Array<std::shared_ptr<EnemyEntity>> ret;

		// 敵
		auto layer = m_tmx.getLayer(U"enemy");
		if (!layer) {
			return ret;
		}
		auto parse = [&](const ObjectGroup& layer) {
			for (const auto& obj : layer.getObjects()) {
				TmxEnemyParser parser(obj);
				if (auto e = parser.parse(); e && e->type != EnemyType::None) {
					ret.push_back(std::move(e));
				}
			}
		};

		TmxParseUtil::ParseForGroup(*layer, parse);

		return ret;
    }
}
