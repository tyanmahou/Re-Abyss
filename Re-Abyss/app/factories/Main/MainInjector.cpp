#include "MainInjector.hpp"

#include <abyss/datastores/Actor/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actor/Gimmick/TmxGimmickDataStore.hpp>
#include <abyss/datastores/Actor/Map/TmxMapDataStore.hpp>
#include <abyss/datastores/Actor/Item/TmxItemDataStore.hpp>
#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
#include <abyss/datastores/BackGround/TmxBackGroundDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorDataStore.hpp>
#include <abyss/datastores/Decor/TmxGraphicsDataStore.hpp>
#include <abyss/datastores/Decor/TmxAnimationDataStore.hpp>

#include <abyss/services/Actor/Item/ItemService.hpp>
#include <abyss/services/Stage/StageService.hpp>
#include <abyss/services/Decor/DecorService.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>

namespace abyss::Factory::Main
{
    emaject::Injector Injector(const s3d::String& mapName)
    {
        emaject::Injector injector;
        injector
            // other
            .install<TiledMapInstaller>(mapName)
            // datastore
            .install<TmxEnemyDataStoreInataller>()
            .install<TmxGimmickDataStoreInataller>()
            .install<TmxMapDataStoreInataller>()
            .install<Actor::Item::TmxItemDataStoreInataller>()
            .install<TmxRoomDataStoreInataller>()
            .install<TmxBackGroundDataStoreInataller>()
            .install<Decor::TmxDecorDataStoreInataller>()
            .install<Decor::TmxGraphicsDataStoreInataller>()
            .install<Decor::TmxAnimationDataStoreInataller>()
            // service
            .install<Actor::Item::ItemServiceInstaller>()
            .install<StageServiceInstaller>()
            .install<BackGroundServiceInstaller>()
            .install<Decor::DecorServiceInstaller>()
            ;
        return injector;
    }
}
