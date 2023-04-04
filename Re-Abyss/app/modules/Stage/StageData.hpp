#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/services/Actor/Enemy/base/IEnemyService.hpp>
#include <abyss/services/Actor/Gimmick/base/IGimmickService.hpp>
#include <abyss/services/Actor/Item/base/IItemService.hpp>
#include <abyss/services/Actor/Land/base/ILandService.hpp>
#include <abyss/services/Room/base/IRoomService.hpp>
#include <abyss/services/Decor/base/IDecorService.hpp>
#include <abyss/services/Attribute/base/IAttributeService.hpp>
#include <abyss/values/StageDef.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class StageData
    {
    public:
        StageData(const StageDef& stage):
            m_stage(stage)
        {}

        s3d::String getMapName() const
        {
            return m_stage.mapName();
        }
        const s3d::Array<RoomEntity>& getRooms() const;
        const s3d::Array<std::shared_ptr<Actor::Land::LandEntity>>& getLands() const;
        const s3d::Array<std::shared_ptr<Actor::Enemy::EnemyEntity>>& getEnemies() const;
        const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& getGimmicks() const;
        const s3d::Array<std::shared_ptr<Actor::Item::ItemEntity>>& getItems() const;

        Decor::IDecorService* getDecorService() const;

        Attribute::IAttributeService* getAttributeService() const;
    private:
        StageDef m_stage;

        [[INJECT(m_roomService)]]
        std::shared_ptr<IRoomService> m_roomService;

        [[INJECT(m_enemyService)]]
        std::shared_ptr<Actor::Enemy::IEnemyService> m_enemyService;
        [[INJECT(m_gimmickService)]]
        std::shared_ptr<Actor::Gimmick::IGimmickService> m_gimmickService;
        [[INJECT(m_itemService)]]
        std::shared_ptr<Actor::Item::IItemService> m_itemService;
        [[INJECT(m_landService)]]
        std::shared_ptr<Actor::Land::ILandService> m_landService;

        [[INJECT(m_decorService)]]
        std::shared_ptr<Decor::IDecorService> m_decorService;

        [[INJECT(m_attributeService)]]
        std::shared_ptr<Attribute::IAttributeService> m_attributeService;
    };
}
