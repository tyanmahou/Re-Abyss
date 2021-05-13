#include "StageService.hpp"
#include <abyss/datastores/Room/base/IRoomDataStore.hpp>
#include <abyss/datastores/Actor/Map/base/IMapDataStore.hpp>
#include <abyss/datastores/Actor/Enemy/base/IEnemyDataStore.hpp>
#include <abyss/datastores/Actor/Gimmick/base/IGimmickDataStore.hpp>

namespace abyss
{
    void StageServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IStageService>()
            .to<StageService>()
            .asCache();
    }
}
