#include "TmxItemParser.hpp"

namespace abyss::Actor::Item
{
    TmxItemParser::TmxItemParser(const s3dTiled::TiledObject& obj):
        m_obj(obj)
    {}

    std::shared_ptr<ItemEntity> TmxItemParser::parse() const
    {
        return std::shared_ptr<ItemEntity>();
    }
}
