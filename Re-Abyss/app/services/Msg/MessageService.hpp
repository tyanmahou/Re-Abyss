#pragma once
#include <abyss/datastores/Msg/base/IMessageDataStore.hpp>
#include <abyss/services/Msg/base/IMessageService.hpp>
#include <Emaject.hpp>

namespace abyss::Resource::Msg
{
    class MessageService final : public IMessageService
    {
    public:
        MessageService(const Language& lang);

        s3d::Array<std::pair<s3d::String, s3d::String>> getMessages(s3d::StringView category)  const override;
    private:
        Language m_lang;
        [[INJECT(m_dataStore)]]
        std::shared_ptr<IMessageDataStore> m_dataStore;
    };

    struct MessageServiceInstaller : emaject::IInstaller
    {
        MessageServiceInstaller(const Language& lang):
            m_lang(lang)
        {
        }
        void onBinding(emaject::Container* container) const override
        {
            container->bind<IMessageService>()
                .to<MessageService>()
                .withArgs(m_lang)
                .asCached();
        }
    private:
        Language m_lang;
    };
}
