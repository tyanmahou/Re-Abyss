#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Item
{
    class IItemService
    {
    public:
        virtual ~IItemService() = default;
        virtual const s3d::Array<std::shared_ptr<ItemEntity>>& getItems() const = 0;
    };
}