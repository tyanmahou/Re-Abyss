#include "StageData.hpp"
namespace abyss
{
    const s3d::Array<BackGroundEntity>& StageData::getBgs() const
    {
        return m_backGroundService->getBgs();
    }
    const s3d::Array<RoomEntity>& StageData::getRooms() const
    {
        return m_roomService->getRooms();
    }
    const s3d::Array<std::shared_ptr<Actor::Map::MapEntity>>& StageData::getMaps() const
    {
        return m_mapService->getMaps();
    }
    const s3d::Array<std::shared_ptr<Actor::Enemy::EnemyEntity>>& StageData::getEnemies() const
    {
        return m_enemyService->getEnemies();
    }
    const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& StageData::getGimmicks() const
    {
        return m_gimmickService->getGimmicks();

    }
    const s3d::Array<std::shared_ptr<Actor::Item::ItemEntity>>& StageData::getItems() const
    {
        return m_itemService->getItems();
    }
    IBackGroundService* StageData::getBackGroundService() const
    {
        return m_backGroundService.get();
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
