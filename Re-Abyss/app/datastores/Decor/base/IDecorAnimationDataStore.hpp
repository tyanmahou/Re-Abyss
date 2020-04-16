#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorAnimationEntity.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class IDecorAnimationDataStore
    {
    public:
        virtual ~IDecorAnimationDataStore() = default;

        virtual s3d::Array<DecorAnimationEntity> select()const = 0;
    };
}