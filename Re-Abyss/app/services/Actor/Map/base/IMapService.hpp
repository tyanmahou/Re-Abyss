#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Map
{
    class IMapService
    {
    public:
        virtual ~IMapService() = default;
        virtual const s3d::Array<std::shared_ptr<MapEntity>>& getMaps() const = 0;
    };
}