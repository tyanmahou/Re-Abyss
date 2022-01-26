#include <abyss/services/Actor/Enemy/EnemyService.hpp>
#include <abyss/datastores/Actor/Enemy/base/IEnemyDataStore.hpp>

namespace abyss::Actor::Enemy
{
    EnemyService::EnemyService(std::shared_ptr<IEnemyDataStore> enemies):
        m_enemies(enemies->select())
    {}

    const s3d::Array<std::shared_ptr<EnemyEntity>>& EnemyService::getEnemies() const
    {
        return m_enemies;
    }

    void EnemyServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IEnemyService>()
            .to<EnemyService>()
            .asCache();
    }
}
