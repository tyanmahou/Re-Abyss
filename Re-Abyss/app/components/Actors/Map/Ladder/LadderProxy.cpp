#include "LadderProxy.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Map::Ladder
{
    LadderProxy::LadderProxy(IActor* pActor)
    {}

    s3d::Line LadderProxy::getCenterLine() const
    {
        return s3d::Line();
    }
    bool LadderProxy::isTop() const
    {
        return false;
    }
}