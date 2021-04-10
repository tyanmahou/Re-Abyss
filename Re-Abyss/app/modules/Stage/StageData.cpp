#include "StageData.hpp"
namespace abyss
{
    const s3d::Array<BackGroundEntity>& StageData::getBgs() const
    {
        return m_backGroundService->getBgs();
    }
    const s3d::Array<RoomEntity>& StageData::getRooms() const
    {
        return m_stageService->getRooms();
    }
    const s3d::Array<std::shared_ptr<MapEntity>>& StageData::getMaps() const
    {
        return m_stageService->getMaps();
    }
    const s3d::Array<std::shared_ptr<EnemyEntity>>& StageData::getEnemies() const
    {
        return m_stageService->getEnemies();
    }
    const s3d::Array<std::shared_ptr<GimmickEntity>>& StageData::getGimmicks() const
    {
        return m_stageService->getGimmicks();

    }
    IBackGroundService* StageData::getBackGroundService() const
    {
        return m_backGroundService.get();
    }
    decor::IDecorService* StageData::getDecorService() const
    {
        return m_decorService.get();
    }
}
