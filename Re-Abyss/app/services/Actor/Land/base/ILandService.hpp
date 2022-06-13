#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Land
{
    class ILandService
    {
    public:
        virtual ~ILandService() = default;
        virtual const s3d::Array<std::shared_ptr<LandEntity>>& getLands() const = 0;
    };
}
