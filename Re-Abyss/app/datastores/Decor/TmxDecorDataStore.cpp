#include "TmxDecorDataStore.hpp"
#include "parser/TmxDecorParser.hpp"
#include <abyss/datastores/base/parser/TmxParseUtil.hpp>

namespace 
{
    using namespace abyss;
    DrawLayer ToDrawLayer(const s3d::String& value)
    {
        if (value == U"decor_back") {
            return DrawLayer::DecorBack;
        }
        if (value == U"decor_middle" || value == U"land") {
            return DrawLayer::DecorMiddle;
        }
        if (value == U"world") {
            return DrawLayer::World;
        }
        if (value == U"decor_front") {
            return DrawLayer::DecorFront;
        }
        return DrawLayer::World;
    }
}
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
            auto drawLayer = ::ToDrawLayer(layer.getProperty(U"layer").value_or(U"decor_middle"));
            for (const auto& obj : layer.getObjects()) {
                TmxDecorParser parser(obj);
                if (auto entity = parser.parse(); entity && entity->type != DecorType::General::None) {
                    entity->layer = drawLayer;
                    entity->parallax = layer.getParallax();
                    ret.push_back(entity);
                }
            }
        };

        TmxParseUtil::ParseForGroup(*layer, parseAll);

        return ret;
    }
}
