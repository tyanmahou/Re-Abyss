#pragma once
#include <abyss/services/Attribute/base/IAttributeService.hpp>
#include <Emaject.hpp>

namespace abyss::Attribute
{
    class IAttributeDataStore;

    class AttributeService : public IAttributeService
    {
    public:
        INJECT_CTOR(AttributeService(
            std::shared_ptr<IAttributeDataStore> attr
        ));

        s3d::Color getBgColor() const override;

    private:
        s3d::Color m_bgColor;
    };

    struct AttributeServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}