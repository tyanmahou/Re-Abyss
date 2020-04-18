#include "DecorService.hpp"
#include <abyss/datastores/Decor/base/IDecorDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/base/IGimmickDataStore.hpp>
#include <abyss/datastores/Actors/Map/base/IMapDataStore.hpp>

#include <abyss/entities/Actors/Gimmick/DoorEntity.hpp>

#include <abyss/translators/Decor/DecorTranslator.hpp>
namespace abyss
{
    DecorService::DecorService(
        std::shared_ptr<IDecorDataStore> decor, 
        std::shared_ptr<IGimmickDataStore> gimmick,
        std::shared_ptr<IMapDataStore> map
    ) {
        auto frontDecors = decor->select(DecorGroup::Front);
        auto backDecors = decor->select(DecorGroup::Back);

        DecorTranslator translator;

        // front
        for (const auto& entity : frontDecors) {
            m_front.push_back(translator.toModel(entity));
        }

        // back
        for (const auto& entity : backDecors) {
            m_back.push_back(translator.toModel(entity));
        }

        // custom
        for (const auto& entity : map->select(false)) {
            m_custom.push_back(translator.toModel(*entity));
        }
        for (const auto& entity : gimmick->select()) {
            if (entity->type == GimmickType::Door) {
                m_custom.push_back(translator.toModel(static_cast<const DoorEntity&>(*entity)));
            }
        }
    }
}
