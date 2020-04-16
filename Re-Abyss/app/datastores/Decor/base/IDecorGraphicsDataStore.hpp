#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorGraphicsEntity.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class IDecorGraphicsDataStore
    {
    public:
        virtual ~IDecorGraphicsDataStore() = default;

        virtual s3d::Array<DecorGraphicsEntity> select()const = 0;
    };
}