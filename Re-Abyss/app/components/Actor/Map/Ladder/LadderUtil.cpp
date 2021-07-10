#include "LadderUtil.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Map::Ladder
{
    s3d::Line LadderUtil::CenterLine(const Physics::TerrainData& terrain)
    {
        const auto& pos = terrain.region.center();
        const auto& size = terrain.region.size;

        Vec2 beginY = pos - Vec2{ 0, size.y / 2.0 + 1.0 };
        Vec2 endY = pos + Vec2{ 0, size.y / 2.0 - 10.0 };
        return s3d::Line(beginY, endY);
    }

    s3d::Vec2 LadderUtil::CenterTopPos(const Physics::TerrainData& terrain)
    {
        const auto& pos = terrain.region.center();
        const auto& size = terrain.region.size;

        return s3d::Vec2{
            pos.x,
            pos.y - size.y / 2.0
        };
    }

    bool LadderUtil::IsTop(const Physics::TerrainData& terrain)
    {
        return (terrain.col & ColDirection::Up) != ColDirection::None;
    }

}
