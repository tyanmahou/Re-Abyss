#pragma once
#include <abyss/services/Actor/Land/base/ILandService.hpp>
#include <Emaject.hpp>

namespace abyss::Actor::Land
{
    class ILandDataStore;

    class LandService : public ILandService
    {
    public:
        INJECT_CTOR(LandService(
            std::shared_ptr<ILandDataStore> lands
        ));
        const s3d::Array<std::shared_ptr<LandEntity>>& getLands() const override;
    private:
        s3d::Array<std::shared_ptr<LandEntity>> m_lands;
    };

    struct LandServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}
