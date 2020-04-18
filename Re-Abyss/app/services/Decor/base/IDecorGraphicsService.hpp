#pragma once
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/entities/Decor/DecorGraphicsEntity.hpp>
#include <abyss/entities/Decor/DecorAnimationEntity.hpp>
namespace abyss
{
    class IDecorGraphicsService
    {
    public:
        using DecorGraphics = s3d::HashTable<s3d::uint32, DecorGraphicsEntity>;
        using DecorAnimations = s3d::HashTable<s3d::uint32, s3d::Array<DecorAnimationEntity>>;
    public:
        virtual ~IDecorGraphicsService() = default;
        virtual const DecorGraphics& getGraphics() const = 0;
        virtual const DecorAnimations& getAnimations() const = 0;
    };
}