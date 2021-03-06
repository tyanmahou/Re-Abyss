#include "BackGroundService.hpp"
#include <abyss/datastores/BackGround/base/IBackGroundDataStore.hpp>

namespace abyss
{
    BackGroundService::BackGroundService(std::shared_ptr<IBackGroundDataStore> dataStore) :
        m_bgs(dataStore->select()),
        m_bgColor(dataStore->getBgColor())
    {}

    const s3d::Array<BackGroundEntity>& abyss::BackGroundService::getBgs() const
    {
        return m_bgs;
    }

    const s3d::Color& BackGroundService::getBgColor() const
    {
        return m_bgColor;
    }

    void BackGroundServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IBackGroundService>()
            .to<BackGroundService>()
            .asCache();
    }
}
