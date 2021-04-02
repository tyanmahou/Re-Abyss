#include "MainInjector.hpp"

#include <abyss/datastores/Actors/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/TmxGimmickDataStore.hpp>
#include <abyss/datastores/Actors/Map/TmxMapDataStore.hpp>
#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
#include <abyss/datastores/BackGround/TmxBackGroundDataStore.hpp>

#include <abyss/services/Stage/StageService.hpp>
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
            .install<TmxRoomDataStoreInataller>()
            .install<TmxBackGroundDataStoreInataller>()
            // service
            .install<StageServiceInstaller>()
            .install<BackGroundServiceInstaller>()
            ;
        return injector;
    }
}
