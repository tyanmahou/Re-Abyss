#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/services/BackGround/base/IBackGroundService.hpp>

namespace abyss
{
    class BackGroundService : public IBackGroundService
    {
        s3d::Array<BackGroundEntity> m_bgs;
        s3d::Color m_bgColor;
    public:
        BackGroundService(std::shared_ptr<IBackGroundDataStore> dataStore);

        const s3d::Array<BackGroundEntity>& getBgs()const override;
        const s3d::Color& getBgColor()const override;
    };
}