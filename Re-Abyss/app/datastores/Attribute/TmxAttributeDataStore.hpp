#pragma once
#include <abyss/datastores/base/TmxDataStore.hpp>
#include <abyss/datastores/Attribute/base/IAttributeDataStore.hpp>

namespace abyss::Attribute
{
    class TmxAttributeDataStore :
        public TmxDataStore,
        public IAttributeDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;
        s3d::Color getBgColor() const override;
    };

    using TmxAttributeDataStoreInataller = TmxDataStoreInataller<IAttributeDataStore, TmxAttributeDataStore>;
}