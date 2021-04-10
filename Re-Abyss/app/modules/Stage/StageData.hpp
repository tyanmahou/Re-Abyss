#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/services/BackGround/BackGroundService.hpp>
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

        [[INJECT(m_decorService)]]
        std::shared_ptr<decor::IDecorService> m_decorService;
    public:
        StageData() = default;
        const s3d::Array<BackGroundEntity>& getBgs() const;

        const s3d::Array<RoomEntity>& getRooms() const;
        const s3d::Array<std::shared_ptr<MapEntity>>& getMaps() const;
        const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const;
        const s3d::Array<std::shared_ptr<GimmickEntity>>& getGimmicks() const;

        IBackGroundService* getBackGroundService() const;
        decor::IDecorService* getDecorService() const;
    };
}