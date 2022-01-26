#include <abyss/datastores/Decor/TmxDecorDataStore.hpp>
#include <abyss/datastores/Decor/parser/TmxDecorParser.hpp>
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>

namespace abyss::Decor
{
    using namespace s3dTiled;

    s3d::Array<std::shared_ptr<DecorEntity>> abyss::Decor::TmxDecorDataStore::select() const
    {
        s3d::Array<std::shared_ptr<DecorEntity>> ret;
        auto layer = m_tmx.getLayer(U"decor");
        if (!layer) {
            return ret;
        }
        auto parseAll = [&](const ObjectGroup& layer) {
            auto drawLayer = Enum::Parse<DrawLayer>(layer.getProperty(U"layer").value_or(U"Land"));
            bool useShadow = layer.getProperty(U"use_shadow").value_or(false);
            for (const auto& obj : layer.getObjects()) {
                TmxDecorParser parser(obj);
                if (auto entity = parser.parse(); entity && entity->type != DecorType::General::None) {
                    entity->layer = drawLayer;
                    entity->parallax = layer.getParallax();
                    entity->useShadow = useShadow;
                    ret.push_back(entity);
                }
            }
        };

        TmxParseUtil::ParseForGroup(*layer, parseAll);

        return ret;
    }
}
