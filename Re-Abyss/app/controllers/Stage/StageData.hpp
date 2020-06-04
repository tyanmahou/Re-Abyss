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
        //const s3d::Array<BackGroundEntity>& getBgs() const;
    };
}