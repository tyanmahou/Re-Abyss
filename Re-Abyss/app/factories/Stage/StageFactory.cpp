#include "StageFactory.hpp"
#include <abyss/controllers/Stage/Stage.hpp>

#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
#include <abyss/datastores/Actors/Map/TmxMapDataStore.hpp>
#include <abyss/datastores/Actors/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/TmxGimmickDataStore.hpp>

#include <abyss/services/Stage/StageService.hpp>

#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/factories/BackGround/BackGroundFactory.hpp>
#include <abyss/factories/Decor/DecorFactory.hpp>

namespace abyss
{
    std::shared_ptr<Stage> StageFactory::CreateFromTmx(const s3d::String& mapName)
    {
        DIContainer c;
        return CreateFromTmx(&c, mapName);

    }
    std::shared_ptr<Stage> StageFactory::CreateFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
        auto decor = DecorFactory::CreateFromTmx(container, mapName);
        auto bg = BackGroundFactory::CreateFromTmx(container, mapName);

        // datastore
        container->regist<IRoomDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxRoomDataStore>(mapName);
        });
        container->regist<IMapDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxMapDataStore>(mapName);
        });
        container->regist<IEnemyDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxEnemyDataStore>(mapName);
        });
        container->regist<IGimmickDataStore>([&mapName](const DIContainer*) {
            return std::make_shared<TmxGimmickDataStore>(mapName);
        });

        // service
        container->regist<IStageService>([](const DIContainer* c) {
            return std::make_shared<StageService>(
                c->get<IRoomDataStore>(),
                c->get<IMapDataStore>(),
                c->get<IEnemyDataStore>(),
                c->get<IGimmickDataStore>()
            );
        });

        // view
        container->regist<Stage>([&](const DIContainer* c) {
            return std::make_shared<Stage>(
                c->get<IStageService>(),
                decor,
                bg
            );
        });
        return container->get<Stage>();
    }
}
