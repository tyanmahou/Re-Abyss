#include "LadderProxy.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Map::Ladder
{
    LadderProxy::LadderProxy(IActor* pActor):
        m_pActor(pActor)
    {}

    void LadderProxy::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<MapProxy>();
        executer.on<IComponent>().addAfter<Terrain>();
    }

    void LadderProxy::onStart()
    {
        m_map = m_pActor->find<MapProxy>();
        m_terrain = m_pActor->find<Terrain>();
    }

    const s3d::Vec2& LadderProxy::getPos() const
    {
        return m_map->getPos();
    }

    s3d::RectF LadderProxy::region() const
    {
        return m_map->region();
    }

    s3d::Line LadderProxy::getCenterLine() const
    {
        const auto& pos = m_map->getPos();
        const auto& size = m_map->getSize();

        Vec2 beginY = pos - Vec2{ 0, size.y / 2.0 + 1.0 };
        Vec2 endY = pos + Vec2{ 0, size.y / 2.0 - 10.0 };
        return s3d::Line(beginY, endY);
    }
    s3d::Vec2 LadderProxy::getCenterTopPos() const
    {
        const auto& pos = m_map->getPos();
        const auto& size = m_map->getSize();

        return s3d::Vec2{
            pos.x,
            pos.y - size.y / 2.0
        };
    }
    bool LadderProxy::isTop() const
    {
        return (m_terrain->getMapColInfo().col & ColDirection::Up) != ColDirection::None;
    }
}