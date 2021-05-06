#include "TmxDecorDataStore.hpp"
#include "parser/TmxDecorParser.hpp"
#include <abyss/utils/Enum/EnumTraits.hpp>

namespace abyss::Decor
{
    using namespace s3dTiled;

    s3d::Array<std::shared_ptr<DecorEntity>> abyss::Decor::TmxDecorDataStore::select() const
    {
        s3d::Array<std::shared_ptr<DecorEntity>> ret;

        auto parseAll = [&](const ObjectGroup& layer) {
            auto drawLayer = Enum::Parse<DrawLayer>(layer.getProperty(U"layer").value_or(U"decor_middle"));
            for (const auto& obj : layer.getObjects()) {
                TmxDecorParser parser(obj);
                if (auto entity = parser.parse(); entity && entity->type != DecorType::General::None) {
                    entity->layer = drawLayer;
                    ret.push_back(entity);
                }
            }
        };

        if (auto&& decor = m_tmx.getLayer(U"decor")) {
            decor->then([&](const GroupLayer& layer) {
                for(auto&& l : layer.getLayers()) {
                    l.then(parseAll);
                }
            });
        }
        return ret;
    }
}
