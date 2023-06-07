#include <abyss/services/Sound/SoundBankService.hpp>
#include <abyss/datastores/Sound/base/ISoundBankDataStore.hpp>

namespace abyss::Sound
{
    SoundBankService::SoundBankService(std::shared_ptr<ISoundBankDataStore> datastore)
    {
        m_settingTable = datastore->select();
    }
    AudioSetting SoundBankService::setting(const SoundLabel& label) const
    {
        if (auto it = m_settingTable.find(label.key()); it != m_settingTable.end()) {
            return it->second;
        }
        return {};
    }
    void SoundBankDataStoreInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<ISoundBankService>()
            .to<SoundBankService>()
            .asCached();
    }
}
