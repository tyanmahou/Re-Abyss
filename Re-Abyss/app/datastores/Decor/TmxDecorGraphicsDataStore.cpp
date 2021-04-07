#include "TmxDecorGraphicsDataStore.hpp"
#include "parser/TmxDecorParser.hpp"

namespace abyss::decor
{
    using namespace s3dTiled;

    s3d::Array<std::shared_ptr<DecorEntity>> abyss::decor::TmxDecorDataStore::select(DecorGroup group) const
    {
        static const std::unordered_map<DecorGroup, s3d::String> toLayerNameMap{
            {DecorGroup::Back, U"back"},
            {DecorGroup::Front, U"front"},
        };

        s3d::Array<std::shared_ptr<DecorEntity>> ret;

        auto parseAll = [&](const ObjectGroup& layer) {
            for (const auto& obj : layer.getObjects()) {
                TmxDecorParser parser(obj);
                if (auto entity = parser.parse(); entity->type != DecorType::Common::None) {
                    ret.push_back(entity);
                }
            }
        };

        if (auto&& decor = m_tmx.getLayer(U"decor")) {
            decor->then([&](const GroupLayer& layer) {
                if (auto l = layer.getLayer(toLayerNameMap.at(group))) {
                    l->then(parseAll);
                }
            });
        }
        return ret;
    }
}
