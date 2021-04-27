#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>
#include <abyss/entities/Decor/DecorGroup.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Decor
{
    class IDecorDataStore
    {
    public:
        virtual ~IDecorDataStore() = default;

        virtual s3d::Array<std::shared_ptr<DecorEntity>> select(DecorGroup group) const = 0;
    };
}