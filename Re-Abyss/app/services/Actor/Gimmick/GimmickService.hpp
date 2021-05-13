#pragma once

#include <abyss/services/Actor/Gimmick/base/IGimmickService.hpp>
#include <Emaject.hpp>

namespace abyss::Actor::Gimmick
{
    class IGimmickDataStore;

    class GimmickService : public IGimmickService
    {
    public:
        INJECT_CTOR(GimmickService(
            std::shared_ptr<IGimmickDataStore> gimmicks
        ));
        const s3d::Array<std::shared_ptr<GimmickEntity>>& getGimmicks() const override;
    private:
        s3d::Array<std::shared_ptr<GimmickEntity>> m_gimmicks;
    };

    struct GimmickServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}