#include "BackGroundFactory.hpp"
#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>
#include <abyss/datastores/BackGround/TmxBackGroundDataStore.hpp>

namespace abyss
{
    void BackGroundFactory::BuildFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        // datastore
        container->regist<IBackGroundDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxBackGroundDataStore>(mapName);
        });

        // service
        container->regist<IBackGroundService>([](const DIContainer* c) {
            return std::make_shared<BackGroundService>(c->get<IBackGroundDataStore>());
        });
    }
}
