#include <abyss/services/Actor/Item/ItemService.hpp>
#include <abyss/datastores/Actor/Item/base/IItemDataStore.hpp>

namespace abyss::Actor::Item
{
    ItemService::ItemService(std::shared_ptr<IItemDataStore> items):
        m_items(items->select())
    {}

    const s3d::Array<std::shared_ptr<ItemEntity>>& ItemService::getItems() const
    {
        return m_items;
    }

    void ItemServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IItemService>()
            .to<ItemService>()
            .asCache();
    }
}
