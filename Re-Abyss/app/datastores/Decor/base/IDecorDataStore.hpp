#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <abyss/entities/Decor/DecorGroup.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::decor
{
    class IDecorDataStore
    {
    public:
        virtual ~IDecorDataStore() = default;

        virtual s3d::Array<DecorEntity> select(DecorGroup group) const = 0;
    };
}