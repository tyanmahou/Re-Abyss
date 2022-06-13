#include <abyss/factories/Main/MainInjector.hpp>

#include <abyss/datastores/Actor/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actor/Gimmick/TmxGimmickDataStore.hpp>
#include <abyss/datastores/Actor/Land/TmxLandDataStore.hpp>
#include <abyss/datastores/Actor/Item/TmxItemDataStore.hpp>
#include <abyss/datastores/Attribute/TmxAttributeDataStore.hpp>
#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
#include <abyss/datastores/BackGround/TmxBackGroundDataStore.hpp>
#include <abyss/datastores/Decor/TmxDecorDataStore.hpp>
#include <abyss/datastores/Decor/TmxGraphicsDataStore.hpp>
#include <abyss/datastores/Decor/TmxAnimationDataStore.hpp>

#include <abyss/services/Actor/Enemy/EnemyService.hpp>
#include <abyss/services/Actor/Gimmick/GimmickService.hpp>
#include <abyss/services/Actor/Item/ItemService.hpp>
#include <abyss/services/Actor/Land/LandService.hpp>
#include <abyss/services/Attribute/AttributeService.hpp>
#include <abyss/services/Room/RoomService.hpp>
#include <abyss/services/Decor/DecorService.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>

namespace abyss::Factory::Main
{
    emaject::Injector Injector(const s3d::String& mapPath)
    {
        emaject::Injector injector;
        injector
            // other
            .install<TiledMapInstaller>(mapPath)
            // datastore
            .install<Actor::Enemy::TmxEnemyDataStoreInataller>()
            .install<Actor::Gimmick::TmxGimmickDataStoreInataller>()
            .install<Actor::Item::TmxItemDataStoreInataller>()
            .install<Actor::Land::TmxLandDataStoreInataller>()
            .install<Attribute::TmxAttributeDataStoreInataller>()
            .install<TmxRoomDataStoreInataller>()
            .install<TmxBackGroundDataStoreInataller>()
            .install<Decor::TmxDecorDataStoreInataller>()
            .install<Decor::TmxGraphicsDataStoreInataller>()
            .install<Decor::TmxAnimationDataStoreInataller>()
            // service
            .install<Actor::Enemy::EnemyServiceInstaller>()
            .install<Actor::Gimmick::GimmickServiceInstaller>()
            .install<Actor::Item::ItemServiceInstaller>()
            .install<Actor::Land::LandServiceInstaller>()
            .install<Attribute::AttributeServiceInstaller>()
            .install<RoomServiceInstaller>()
            .install<BackGroundServiceInstaller>()
            .install<Decor::DecorServiceInstaller>()
            ;
        return injector;
    }
}
