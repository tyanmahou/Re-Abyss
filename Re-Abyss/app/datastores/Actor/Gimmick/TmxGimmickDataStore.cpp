#include "TmxGimmickDataStore.hpp"
#include "parser/TmxGimmickParser.hpp"
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

namespace abyss::Actor::Gimmick
{
    using namespace s3d;
    using namespace s3dTiled;

    s3d::Array<std::shared_ptr<GimmickEntity>> TmxGimmickDataStore::select() const
    {
		s3d::Array<std::shared_ptr<GimmickEntity>> ret;

		// ギミック
		auto layer = m_tmx.getLayer(U"gimmick");
		if (!layer) {
			return ret;
		}
		auto parse = [&](const ObjectGroup& layer) {
			for (const auto& obj : layer.getObjects()) {
				TmxGimmickParser parser(obj);
				if (auto e = parser.parse(); e && e->type != GimmickType::None) {
					ret.push_back(std::move(e));
				}
			}
		};

		TmxParseUtil::ParseForGroup(*layer, parse);

		return ret;
    }
}
