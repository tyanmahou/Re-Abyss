#include "PenetrateFloorProxy.hpp"

namespace abyss::Actor::Map::PenetrateFloor
{
    PenetrateFloorProxy::PenetrateFloorProxy(IActor* pActor, bool canDown, ColDirection aroundFloor):
        m_pActor(pActor),
        m_canDown(canDown),
        m_aroundFloor(aroundFloor)
    {}
    void PenetrateFloorProxy::setup(Depends depends)
    {
        depends.on<IComponent>().addAfter<MapProxy>();
        depends.on<IComponent>().addAfter<Terrain>();
    }
    void PenetrateFloorProxy::onStart()
    {
        m_map = m_pActor->find<MapProxy>();
        m_terrain = m_pActor->find<Terrain>();
    }
    const s3d::Vec2& PenetrateFloorProxy::getPos() const
    {
        return m_map->getPos();
    }
    s3d::RectF PenetrateFloorProxy::region() const
    {
        return m_map->region();
    }
    bool PenetrateFloorProxy::canDown() const
    {
        return m_canDown;
    }
    bool PenetrateFloorProxy::tryDown(const s3d::RectF& region) const
    {
        if (!m_canDown) {
            return false;
        }
        const auto& own = this->region();
        if (m_aroundFloor.isLeft() && own.x > region.x) {
            return false;
        }

        if (m_aroundFloor.isRight() && own.x + own.w < region.x + region.w) {
            return false;
        }
        return true;
    }
}
