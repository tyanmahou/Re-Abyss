#include "StageService.hpp"
#include <abyss/datastores/Room/base/IRoomDataStore.hpp>
#include <abyss/datastores/Actor/Map/base/IMapDataStore.hpp>
#include <abyss/datastores/Actor/Enemy/base/IEnemyDataStore.hpp>
#include <abyss/datastores/Actor/Gimmick/base/IGimmickDataStore.hpp>

namespace abyss
{
    StageService::StageService(
        std::shared_ptr<IRoomDataStore> rooms, 
        std::shared_ptr<IMapDataStore> maps, 
        std::shared_ptr<IEnemyDataStore> enemies,
        std::shared_ptr<IGimmickDataStore> gimmicks
    ):
        m_rooms(rooms->select()),
        m_maps(maps->selectFiltered()),
        m_enemies(enemies->select()),
        m_gimmicks(gimmicks->select())
    {}
    void StageServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IStageService>()
            .to<StageService>()
            .asCache();
    }
}
