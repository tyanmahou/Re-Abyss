#pragma once
#include <abyss/modules/Physics/base/TerrainData.hpp>
#include <Siv3D/Line.hpp>

namespace abyss::Actor::Land::Ladder
{
    class LadderUtil
    {
    public:
        static s3d::Line CenterLine(const Physics::TerrainData& terrain);

        static s3d::Vec2 CenterTopPos(const Physics::TerrainData& terrain);

        static bool IsTop(const Physics::TerrainData& terrain);
    };
}
