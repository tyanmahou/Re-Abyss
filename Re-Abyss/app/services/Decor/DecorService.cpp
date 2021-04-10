#include "DecorService.hpp"

#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>
#include <abyss/datastores/Decor/base/IAnimationDataStore.hpp>
#include <abyss/datastores/Decor/base/IGraphicsDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/base/IGimmickDataStore.hpp>
#include <abyss/datastores/Actors/Map/base/IMapDataStore.hpp>

namespace abyss::decor
{
    DecorService::DecorService(
        std::shared_ptr<IDecorDataStore>decor, 
        std::shared_ptr<IGimmickDataStore>gimmick,
        std::shared_ptr<IMapDataStore>map,
        std::shared_ptr<IGraphicsDataStore> graphics,
        std::shared_ptr<IAnimationDataStore> animation
    )
    {
        m_front = decor->select(DecorGroup::Front);
        m_back = decor->select(DecorGroup::Back);

        m_graphics = graphics->selectWithKey();
        m_animation = animation->selectWithKey();
    }
    void DecorServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IDecorService>()
            .to<DecorService>()
            .asCache();
    }
}
