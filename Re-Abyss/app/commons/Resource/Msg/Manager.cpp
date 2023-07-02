#include <abyss/commons/Resource/Msg/Manager.hpp>
#include <abyss/commons/Resource/Msg/MessageTable.hpp>
#include <abyss/commons/Resource/Preload/Preloader.hpp>

#include <abyss/services/Msg/base/IMessageService.hpp>
#include <abyss/commons/Factory/Message/Injector.hpp>
#include <Siv3D.hpp>

namespace abyss::Resource::Msg
{
    class Manager::Impl
    {
    public:
        void load(const Language& lang, Assets* pAssets)
        {
            if (auto service = Factory::Message::Injector(lang, pAssets).resolve<IMessageService>()) {
                this->load(U"Chara", service);
                this->load(U"Common", service);
                this->load(U"SaveSelect", service);
                this->load(U"Title", service);
                this->load(U"Home", service);
            }
        }
        void load(s3d::StringView category, const std::shared_ptr<IMessageService>& service)
        {
            for (auto&& [key, message] : service->getMessages(category)) {
                m_table.add(category, key, std::move(message));
            }
        }
        const s3d::String& get(const Label& label)
        {
            return m_table.get(label);
        }
    private:
        MessageTable m_table;
    };

    Manager::Manager():
        m_pImpl(std::make_unique<Impl>())
    {}

    void Manager::Load(const Language& lang, Assets* pAssets)
    {
        return Instance()->m_pImpl->load(lang, pAssets);
    }

    const s3d::String& Manager::Get(const Label& label)
    {
        return Instance()->m_pImpl->get(label);
    }
}
