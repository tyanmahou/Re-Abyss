#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <Siv3D/HashTable.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Decor/GraphicsEntity.hpp>

namespace abyss::decor
{
    class IDecorService
    {
    public:
        using DecorGraphics = s3d::HashTable<s3d::uint32, GraphicsEntity>;
        using DecorAnimations = s3d::HashTable<s3d::uint32, s3d::Array<AnimationEntity>>;
    public:
        virtual ~IDecorService() = default;

        virtual const s3d::Array<std::shared_ptr<DecorEntity>>& getFront() const = 0;
        virtual const s3d::Array<std::shared_ptr<DecorEntity>>& getBack() const = 0;
        virtual const s3d::Array<std::shared_ptr<DecorEntity>>& getCustom() const = 0;

        virtual s3d::Array<std::shared_ptr<DecorEntity>> getTileMap(const s3d::RectF& screen) const = 0;

        virtual const DecorGraphics& getGraphics() const = 0;
        virtual const DecorAnimations& getAnimations() const = 0;
    };
}
