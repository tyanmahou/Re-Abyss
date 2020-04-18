#include "DecorFactory.hpp"
#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/datastores/Decor/TmxDecorDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorGraphicsDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorAnimationDataStore.hpp>

#include <abyss/datastores/Actors/Map/TmxMapDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/TmxGimmickDataStore.hpp>

#include <abyss/services/Decor/DecorService.hpp>
#include <abyss/services/Decor/DecorGraphicsService.hpp>

#include <abyss/controllers/Decor/Decor.hpp>
#include <abyss/controllers/Decor/DecorGraphicsManager.hpp>

namespace abyss
{
    std::shared_ptr<Decor> abyss::DecorFactory::CreateFromTmx(const s3d::String& mapName)
    {
        DIContainer c;
        return CreateFromTmx(&c, mapName);
    }
    std::shared_ptr<Decor> DecorFactory::CreateFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        //datastores
        container->regist<IDecorDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxDecorDataStore>(mapName);
        });
        container->regist<IDecorGraphicsDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxDecorGraphicsDataStore>(mapName);
        });
        container->regist<IDecorAnimationDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxDecorAnimationDataStore>(mapName);
        });
        container->regist<IGimmickDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxGimmickDataStore>(mapName);
        });
        container->regist<IMapDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxMapDataStore>(mapName);
        });

        // services
        container->regist<IDecorGraphicsService>([](const DIContainer* c) {
            return std::make_shared<DecorGraphicsService>(
                c->get<IDecorGraphicsDataStore>(),
                c->get<IDecorAnimationDataStore>()
            );
        });
        container->regist<IDecorService>([](const DIContainer* c) {
            return std::make_shared<DecorService>(
                c->get<IDecorDataStore>(),
                c->get<IGimmickDataStore>(),
                c->get<IMapDataStore>()
            );
        });

        // controllers
        container->regist<DecorGraphicsManager>([](const DIContainer* c) {
            return std::make_shared<DecorGraphicsManager>(
                c->get<IDecorGraphicsService>()
            );
        });
        container->regist<Decor>([](const DIContainer* c) {
            return std::make_shared<Decor>(
                c->get<IDecorService>(),
                c->get<DecorGraphicsManager>()
            );
        });

        return container->get<Decor>();
    }
}
