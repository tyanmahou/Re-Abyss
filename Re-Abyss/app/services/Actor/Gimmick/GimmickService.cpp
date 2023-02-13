#include <abyss/services/Actor/Gimmick/GimmickService.hpp>
#include <abyss/datastores/Actor/Gimmick/base/IGimmickDataStore.hpp>

namespace abyss::Actor::Gimmick
{
    GimmickService::GimmickService(std::shared_ptr<IGimmickDataStore> gimmicks) :
        m_gimmicks(gimmicks->select())
    {}

    const s3d::Array<std::shared_ptr<GimmickEntity>>& GimmickService::getGimmicks() const
    {
        return m_gimmicks;
    }

    void GimmickServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IGimmickService>()
            .to<GimmickService>()
            .asCached();
    }
}
