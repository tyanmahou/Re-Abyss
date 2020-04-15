#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class IBackGroundDataStore
    {
    public:
        virtual ~IBackGroundDataStore() = default;

        virtual s3d::Array<BackGroundEntity> select()const = 0;
    };
}