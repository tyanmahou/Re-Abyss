#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/entities/Actor/Land/LandEntity.hpp>

namespace abyss::Actor::Land
{
    class ILandDataStore
    {
    public:
        virtual ~ILandDataStore() = default;

        s3d::Array<std::shared_ptr<LandEntity>> selectFiltered() const
        {
            return this->select(true);
        }
        virtual s3d::Array<std::shared_ptr<LandEntity>> select(bool isMerge = true)const = 0;
    };
}
