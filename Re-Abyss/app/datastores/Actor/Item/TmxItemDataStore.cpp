#include "TmxItemDataStore.hpp"

namespace abyss::Actor::Item
{
    using namespace s3d;
    using namespace s3dTiled;

    s3d::Array<std::shared_ptr<ItemEntity>> TmxItemDataStore::select() const
    {
        s3d::Array<std::shared_ptr<ItemEntity>> ret;
        // 敵
        auto layer = m_tmx.getLayer(U"item");
        if (!layer) {
            return ret;
        }
        auto parse = [&](const ObjectGroup& layer) {
            for (const auto& obj : layer.getObjects()) {
                // TODO パース処理
            }
        };
        layer->then(parse);
        return ret;
    }
}
