#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>
#include <abyss/services/Actor/Enemy/base/IEnemyService.hpp>
#include <abyss/services/Actor/Gimmick/base/IGimmickService.hpp>
#include <abyss/services/Actor/Item/base/IItemService.hpp>
#include <abyss/services/Actor/Map/base/IMapService.hpp>
#include <abyss/services/Stage/StageService.hpp>
#include <abyss/services/Decor/DecorService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class StageData
    {
        [[INJECT(m_backGroundService)]]
        std::shared_ptr<IBackGroundService> m_backGroundService;

        [[INJECT(m_stageService)]]
        std::shared_ptr<IStageService> m_stageService;

        [[INJECT(m_enemyService)]]
        std::shared_ptr<Actor::Enemy::IEnemyService> m_enemyService;
        [[INJECT(m_gimmickService)]]
        std::shared_ptr<Actor::Gimmick::IGimmickService> m_gimmickService;
        [[INJECT(m_itemService)]]
        std::shared_ptr<Actor::Item::IItemService> m_itemService;
        [[INJECT(m_mapService)]]
        std::shared_ptr<Actor::Map::IMapService> m_mapService;

        [[INJECT(m_decorService)]]
        std::shared_ptr<Decor::IDecorService> m_decorService;
    public:
        StageData() = default;
        const s3d::Array<BackGroundEntity>& getBgs() const;

        const s3d::Array<RoomEntity>& getRooms() const;
        const s3d::Array<std::shared_ptr<Actor::Map::MapEntity>>& getMaps() const;
        const s3d::Array<std::shared_ptr<Actor::Enemy::EnemyEntity>>& getEnemies() const;
        const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& getGimmicks() const;
        const s3d::Array<std::shared_ptr<Actor::Item::ItemEntity>>& getItems() const;

        IBackGroundService* getBackGroundService() const;
        Decor::IDecorService* getDecorService() const;
    };
}