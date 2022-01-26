#include <abyss/datastores/Actor/Item/TmxItemDataStore.hpp>
#include <abyss/datastores/Actor/Item/parser/TmxItemParser.hpp>
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

namespace abyss::Actor::Item
{
    using namespace s3d;
    using namespace s3dTiled;

    s3d::Array<std::shared_ptr<ItemEntity>> TmxItemDataStore::select() const
    {
        s3d::Array<std::shared_ptr<ItemEntity>> ret;
        // アイテム
        auto layer = m_tmx.getLayer(U"item");
        if (!layer) {
            return ret;
        }
        auto parse = [&](const ObjectGroup& layer) {
            for (const auto& obj : layer.getObjects()) {
                TmxItemParser parser(obj);
                if (auto e = parser.parse(); e && e->type != ItemType::None) {
                    ret.push_back(std::move(e));
                }
            }
        };

        TmxParseUtil::ParseForGroup(*layer, parse);

        return ret;
    }
}
