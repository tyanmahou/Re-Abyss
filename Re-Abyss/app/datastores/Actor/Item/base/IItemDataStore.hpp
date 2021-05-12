#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/entities/Actor/Item/ItemEntity.hpp>

namespace abyss::Actor::Item
{
    class IItemDataStore
    {
    public:
        virtual ~IItemDataStore() = default;

        virtual s3d::Array<std::shared_ptr<ItemEntity>> select()const = 0;
    };
}