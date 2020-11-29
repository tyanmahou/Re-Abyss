#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor::Map::Ladder
{
    class LadderProxy :
        public IComponent
    {
        LadderProxy(IActor* pActor);

        s3d::Line getCenterLine() const;
        bool isTop() const;
    };
}