#include "TmxDecorGraphicsDataStore.hpp"

namespace abyss::decor
{
    using namespace s3dTiled;

    s3d::Array<DecorEntity> abyss::decor::TmxDecorDataStore::select(DecorGroup group) const
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
                    .type = Motif::Common::Common,
                    .pos = pos,
                    .size = size,
                    .rotation = obj.rotation,
                    .isMirrored = obj.isMirrored,
                    .isFlipped = obj.isFliped,
                };
                ret.push_back(entity);
            }
        };

        if (auto&& decor = m_tmx.getLayer(U"decor")) {
            decor->then([&](const GroupLayer& layer) {
                if (auto l = layer.getLayer(toLayerNameMap.at(group))) {
                    l->then(parser);
                }
            });
        }
        return ret;
    }
}
