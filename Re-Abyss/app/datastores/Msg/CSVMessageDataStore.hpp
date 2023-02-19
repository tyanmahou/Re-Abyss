#pragma once
#include <abyss/datastores/Msg/base/IMessageDataStore.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Emaject.hpp>

namespace abyss::Resource::Msg
{
    class CSVMessageDataStore final : public IMessageDataStore
    {
    public:
        CSVMessageDataStore(Assets* pAssets);

    public:
        s3d::Array<std::pair<s3d::String, s3d::String>> select(s3d::StringView category, const Language& lang) const override;
    private:
        Assets* m_pAssets;
    };

    struct CSVMessageDataStoreInstaller : emaject::IInstaller
    {
        CSVMessageDataStoreInstaller(Assets* pAssets):
            m_pAssets(pAssets)
        {
        }
        void onBinding(emaject::Container* container) const override
        {
            container->bind<IMessageDataStore>()
                .to<CSVMessageDataStore>()
                .withArgs(m_pAssets)
                .asCached();
        }
    private:
        Assets* m_pAssets = nullptr;
    };
}
