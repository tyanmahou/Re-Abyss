#include "DecorService.hpp"

#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>
#include <abyss/datastores/Decor/base/IAnimationDataStore.hpp>
#include <abyss/datastores/Decor/base/IGraphicsDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/base/IGimmickDataStore.hpp>
#include <abyss/datastores/Actors/Map/base/IMapDataStore.hpp>

#include <abyss/translators/Decor/DecorTranslator.hpp>

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

        // Custom
        {
            DecorTranslator translator;

            auto mapEntities = map->select(false);
            m_custom.reserve(mapEntities.size());
            for (const auto& entity : mapEntities) {
                m_custom.push_back(translator.toEntity(*entity));
            }
        }
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
