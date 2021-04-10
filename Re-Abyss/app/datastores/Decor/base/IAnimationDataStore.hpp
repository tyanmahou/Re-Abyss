#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/AnimationEntity.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
namespace abyss::decor
{
    class IAnimationDataStore
    {
    public:
        virtual ~IAnimationDataStore() = default;

        virtual s3d::Array<AnimationEntity> select()const = 0;
        s3d::HashTable<s3d::uint32, s3d::Array<AnimationEntity>> selectWithKey()const;
    };
}