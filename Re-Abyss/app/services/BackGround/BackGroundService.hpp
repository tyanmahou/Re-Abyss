#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/services/BackGround/base/IBackGroundService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class IBackGroundDataStore;

    class BackGroundService : public IBackGroundService
    {
        s3d::Array<BackGroundEntity> m_bgs;
        s3d::Color m_bgColor;
    public:
        INJECT_CTOR(BackGroundService(std::shared_ptr<IBackGroundDataStore> dataStore));

        const s3d::Array<BackGroundEntity>& getBgs()const override;
    };

    struct BackGroundServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}