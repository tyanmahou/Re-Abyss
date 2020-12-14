#include "MainInjector.hpp"

#include <abyss/datastores/Actors/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actors/Gimmick/TmxGimmickDataStore.hpp>
#include <abyss/datastores/Actors/Map/TmxMapDataStore.hpp>
#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
#include <abyss/datastores/BackGround/TmxBackGroundDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorGraphicsDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorAnimationDataStore.hpp>

namespace abyss::Factory::Main
{
    emaject::Injector Injector(const s3d::String& mapName)
    {
        emaject::Injector injector;
        injector
            .install<TiledMapInstaller>(mapName)
            .install<TmxEnemyDataStoreInataller>()
            .install<TmxGimmickDataStoreInataller>()
            .install<TmxMapDataStoreInataller>()
            .install<TmxRoomDataStoreInataller>()
            .install<TmxBackGroundDataStoreInataller>()
            .install<TmxDecorDataStoreInataller>()
            .install<TmxDecorGraphicsDataStoreInataller>()
            .install<TmxDecorAnimationDataStoreInataller>()
            ;
        return injector;
    }
}
