#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/DecorAnimationEntity.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
namespace abyss
{
    class IDecorAnimationDataStore
    {
    public:
        virtual ~IDecorAnimationDataStore() = default;

        virtual s3d::Array<DecorAnimationEntity> select()const = 0;
        s3d::HashTable<s3d::uint32, s3d::Array<DecorAnimationEntity>> selectWithKey()const;
    };
}