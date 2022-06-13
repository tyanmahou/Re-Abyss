#include <abyss/components/Actor/Land/PenetrateFloor/PenetrateFloorExtension.hpp>

namespace abyss::Actor::Land::PenetrateFloor
{
    PenetrateFloorExtension::PenetrateFloorExtension(bool canDown, ColDirection aroundFloor):
        m_canDown(canDown),
        m_aroundFloor(aroundFloor)
    {}

    bool PenetrateFloorExtension::tryDown(const Physics::TerrainData & terrain, const s3d::RectF & region) const
    {
        if (!m_canDown) {
            return false;
        }
        const auto& own = terrain.region;
        if (m_aroundFloor.isLeft() && own.x > region.x) {
            return false;
        }

        if (m_aroundFloor.isRight() && own.x + own.w < region.x + region.w) {
            return false;
        }
        return true;
    }

}
