#pragma once
#include <abyss/services/Sound/base/ISoundBankService.hpp>
#include <Siv3D/HashTable.hpp>
#include <Emaject.hpp>

namespace abyss::Sound
{
    class ISoundBankDataStore;

    class SoundBankService: public ISoundBankService
    {
    public:
        INJECT_CTOR(SoundBankService(
            std::shared_ptr<ISoundBankDataStore> datastore
        ));
        AudioSetting setting(const SoundLabel& label) const override;
    private:
        s3d::HashTable<s3d::String, AudioSetting> m_settingTable;
    };

    struct SoundBankServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}
