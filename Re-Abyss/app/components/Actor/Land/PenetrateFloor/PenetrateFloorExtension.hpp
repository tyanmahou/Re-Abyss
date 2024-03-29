#pragma once
#include <abyss/utils/Collision/ColDirection.hpp>
#include <abyss/modules/Physics/base/TerrainData.hpp>

namespace abyss::Actor::Land::PenetrateFloor
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
