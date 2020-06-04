#include "StageDataFactory.hpp"

#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
#include <abyss/datastores/Actors/Map/TmxMapDataStore.hpp>
#include <abyss/datastores/Actors/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/TmxGimmickDataStore.hpp>

#include <abyss/services/Stage/StageService.hpp>

#include <abyss/factories/DIContainer/DIContainer.hpp>
#include <abyss/factories/BackGround/BackGroundFactory.hpp>
#include <abyss/factories/Decor/DecorFactory.hpp>

#include <abyss/controllers/Stage/StageData.hpp>

#include <abyss/services/BackGround/base/IBackGroundService.hpp>
#include <abyss/services/Decor/base/IDecorService.hpp>
#include <abyss/services/Decor/base/IDecorGraphicsService.hpp>

namespace abyss
{
    void StageDataFactory::BuildFromTmx(const DIContainer* container, const s3d::String& mapName)
    {
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

        // controller
        container->regist<StageData>([](const DIContainer* c) {
            return std::make_shared<StageData>(
                c->get<IBackGroundService>(),
                c->get<IDecorService>(),
                c->get<IDecorGraphicsService>(),
                c->get<IStageService>()
                );
        });
    }
    std::shared_ptr<StageData> abyss::StageDataFactory::CreateFromTmx(const s3d::String& mapName)
    {
        DIContainer c;
        BackGroundFactory::BuildFromTmx(&c, mapName);
        DecorFactory::BuildFromTmx(&c, mapName);
        StageDataFactory::BuildFromTmx(&c, mapName);
        return c.get<StageData>();
    }

}
