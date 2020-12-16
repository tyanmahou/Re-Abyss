#include "LadderProxy.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Map::Ladder
{
    LadderProxy::LadderProxy(IActor* pActor):
        m_pActor(pActor)
    {}

    void LadderProxy::setup(Depends depends)
    {
        depends.addAfter<MapParam>();
        depends.addAfter<Terrain>();
    }

    void LadderProxy::onStart()
    {
        m_mapParam = m_pActor->find<MapParam>();
        m_terrain = m_pActor->find<Terrain>();
    }

    s3d::Line LadderProxy::getCenterLine() const
    {
        const auto& pos = m_mapParam->getPos();
        const auto& size = m_mapParam->getSize();

        Vec2 beginY = pos - Vec2{ 0, size.y / 2.0 + 1.0 };
        Vec2 endY = pos + Vec2{ 0, size.y / 2.0 - 10.0 };
        return s3d::Line(beginY, endY);
    }
    bool LadderProxy::isTop() const
    {
        return (m_terrain->getMapColInfo().col & ColDirection::Up) != ColDirection::None;
    }
}