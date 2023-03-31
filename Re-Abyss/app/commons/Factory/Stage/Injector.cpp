#include <abyss/commons/Factory/Stage/Injector.hpp>

#include <abyss/datastores/Actor/Enemy/TmxEnemyDataStore.hpp>
#include <abyss/datastores/Actor/Gimmick/TmxGimmickDataStore.hpp>
#include <abyss/datastores/Actor/Land/TmxLandDataStore.hpp>
#include <abyss/datastores/Actor/Item/TmxItemDataStore.hpp>
#include <abyss/datastores/Attribute/TmxAttributeDataStore.hpp>
#include <abyss/datastores/Room/TmxRoomDataStore.hpp>
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

namespace abyss::Factory::Stage
{
    emaject::Injector Injector(const s3d::String& mapPath)
    {
        emaject::Injector injector;
        Install(injector, mapPath);
        return injector;
    }
    void Install(emaject::Injector& injector, const s3d::String& mapPath)
    {
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
            .install<Decor::DecorServiceInstaller>()
            ;
    }
}
