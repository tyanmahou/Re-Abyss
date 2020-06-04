#include "BackGroundFactory.hpp"
#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>
#include <abyss/datastores/BackGround/TmxBackGroundDataStore.hpp>

namespace abyss
{
    std::shared_ptr<BackGround> BackGroundFactory::CreateFromTmx(const s3d::String& mapName)
    {
        DIContainer c;
        return CreateFromTmx(&c, mapName);
    }
    std::shared_ptr<BackGround> BackGroundFactory::CreateFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        // datastore
        container->regist<IBackGroundDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxBackGroundDataStore>(mapName);
        });

        // service
        container->regist<IBackGroundService>([](const DIContainer* c) {
            return std::make_shared<BackGroundService>(c->get<IBackGroundDataStore>());
        });

        // controller
        container->regist<BackGround>([](const DIContainer* c) {
            return std::make_shared<BackGround>();
        });
        return container->get<BackGround>();
    }
}
