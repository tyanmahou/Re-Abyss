#include "AttributeService.hpp"
#include <abyss/datastores/Attribute/base/IAttributeDataStore.hpp>

namespace abyss::Attribute
{
    AttributeService::AttributeService(std::shared_ptr<IAttributeDataStore> attr):
        m_bgColor(attr->getBgColor())
    {}

    s3d::Color AttributeService::getBgColor() const
    {
        return m_bgColor;
    }

    void AttributeServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IAttributeService>()
            .to<AttributeService>()
            .asCache();
    }
}
