#pragma once

#include <abyss/services/Actor/Item/base/IItemService.hpp>
#include <Emaject.hpp>

namespace abyss::Actor::Item
{
    class IItemDataStore;

    class ItemService : public IItemService
    {
    public:
        INJECT_CTOR(ItemService(
            std::shared_ptr<IItemDataStore> items
        ));
        const s3d::Array<std::shared_ptr<ItemEntity>>& getItems() const override;
    private:
        s3d::Array<std::shared_ptr<ItemEntity>> m_items;
    };

    struct ItemServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}