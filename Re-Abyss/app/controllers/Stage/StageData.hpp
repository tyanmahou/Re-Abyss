#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class StageData
    {
        std::shared_ptr<IBackGroundService> m_backGroundService;
        std::shared_ptr<IDecorService> m_decorService;
        std::shared_ptr<IDecorGraphicsService> m_decorGraphicsService;
        // FIXME StageServiceやめたい
        std::shared_ptr<IStageService> m_stageService;
    public:
        StageData() = default;
        StageData(
            std::shared_ptr<IBackGroundService> bg,
            std::shared_ptr<IDecorService> decor,
            std::shared_ptr<IDecorGraphicsService> decorGraphics,
            std::shared_ptr<IStageService> stage
        );
        const s3d::Array<BackGroundEntity>& getBgs() const;

        const s3d::Array<RoomEntity>& getRooms() const;
        const s3d::Array<std::shared_ptr<MapEntity>>& getMaps() const;
        const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const;
        const s3d::Array<std::shared_ptr<GimmickEntity>>& getGimmicks() const;

        IDecorService* getDecorService() const;
        IDecorGraphicsService* getDecorGraphicsService() const;
    };
}