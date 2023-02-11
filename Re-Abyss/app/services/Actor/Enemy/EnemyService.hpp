#pragma once

#include <abyss/services/Actor/Enemy/base/IEnemyService.hpp>
#include <Emaject.hpp>

namespace abyss::Actor::Enemy
{
    class IEnemyDataStore;

    class EnemyService : public IEnemyService
    {
    public:
        INJECT_CTOR(EnemyService(
            std::shared_ptr<IEnemyDataStore> enemies
        ));
        const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const override;
    private:
        s3d::Array<std::shared_ptr<EnemyEntity>> m_enemies;
    };

    struct EnemyServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}
