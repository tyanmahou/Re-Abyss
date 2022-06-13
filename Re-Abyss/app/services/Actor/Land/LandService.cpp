#include <abyss/services/Actor/Land/LandService.hpp>
#include <abyss/datastores/Actor/Land/base/ILandDataStore.hpp>

namespace abyss::Actor::Land
{
    LandService::LandService(std::shared_ptr<ILandDataStore> lands):
        m_lands(lands->select())
    {}

    const s3d::Array<std::shared_ptr<LandEntity>>& LandService::getLands() const
    {
        return m_lands;
    }

    void LandServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<ILandService>()
            .to<LandService>()
            .asCache();
    }
}
