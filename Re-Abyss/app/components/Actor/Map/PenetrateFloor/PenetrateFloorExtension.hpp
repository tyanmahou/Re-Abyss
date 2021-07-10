#pragma once
#include <abyss/types/ColDirection.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>

namespace abyss::Actor::Map::PenetrateFloor
{
    class PenetrateFloorExtension : public Physics::ITerrainExtData
    {
    public:
        PenetrateFloorExtension(bool canDown, ColDirection aroundFloor);

        bool canDown() const
        {
            return m_canDown;
        }

        bool tryDown(const Physics::TerrainData& terrain, const s3d::RectF& region) const;
    private:
        bool m_canDown;
        ColDirection m_aroundFloor;
    };
}