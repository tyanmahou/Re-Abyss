#include <abyss/modules/Stage/StageData.hpp>

namespace abyss
{
    const s3d::Array<RoomEntity>& StageData::getRooms() const
    {
        return m_roomService->getRooms();
    }
    const s3d::Array<std::shared_ptr<Actor::Land::LandEntity>>& StageData::getLands() const
    {
        return m_landService->getLands();
    }
    const s3d::Array<std::shared_ptr<Actor::Enemy::EnemyEntity>>& StageData::getEnemies() const
    {
        return m_enemyService->getEnemies();
    }
    const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& StageData::getGimmicks() const
    {
        if (!m_gimmickService) {
            return {};
        }
        return m_gimmickService->getGimmicks();

    }
    const s3d::Array<std::shared_ptr<Actor::Item::ItemEntity>>& StageData::getItems() const
    {
        return m_itemService->getItems();
    }
    Decor::IDecorService* StageData::getDecorService() const
    {
        return m_decorService.get();
    }
    Attribute::IAttributeService* StageData::getAttributeService() const
    {
        return m_attributeService.get();
    }
}
